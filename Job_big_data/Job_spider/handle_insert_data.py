# -*- coding: utf-8 -*-
# @Author: Vincent Vic
# @Date:   2019-08-6 18:18:16
# @Last Modified by:   Vincent Vic
# @Last Modified time: 2019-08-14 20:11:29
# @function:数据库的查找，存储

import re
import time
from collections import Counter
from Job_spider.create_job_tables import Jobtables
from Job_spider.create_job_tables import Session

#数据操作类
class HandleData(object):
    def __init__(self):
        #实例化session信息
        self.mysql_session=Session()
        #获取当日日期信息
        self.date=time.strftime("%Y-%m-%d",time.localtime())#'2019-08-10'

    #数据存储的方法
    def insert_item(self,item):
        #获取当日日期信息
        date=time.strftime("%Y-%m-%d",time.localtime())
        #通过自己创建的数据类，存储数据，创建对象
        data = Jobtables(
            # 岗位ID
            positionID=item['positionId'],
            # 经度
            longitude=item['longitude'],
            # 纬度
            latitude=item['latitude'],
            # 岗位名称
            positionName=item['positionName'],
            # 工作年限
            workYear=item['workYear'],
            # 学历
            education=item['education'],
            # 岗位性质
            jobNature=item['jobNature'],
            # 公司类型
            financeStage=item['financeStage'],
            # 公司规模
            companySize=item['companySize'],
            # 业务方向
            industryField=item['industryField'],
            # 所在城市
            city=item['city'],
            # 岗位标签
            positionAdvantage=item['positionAdvantage'],
            # 公司简称
            companyShortName=item['companyShortName'],
            # 公司全称
            companyFullName=item['companyFullName'],
            # 公司所在区
            district=item['district'],
            # 公司福利标签
            companyLabelList=','.join(item['companyLabelList']),
            salary=item['salary'],
            # 抓取日期
            crawl_date=date
        )
        # 在存储数据之前，先来查询一下表里是否有这条岗位信息
        query_result = self.mysql_session.query(Jobtables).filter(Jobtables.crawl_date == self.date,
                                                                    Jobtables.positionID == item[
                                                                        'positionId']).first()
        #判断查询结果
        if query_result:
            print('该岗位信息已存在%s:%s:%s'%(item['positionId'],item['city'],item['positionName']))
        else:
            # 插入数据
            self.mysql_session.add(data)
            # 提交数据到数据库
            self.mysql_session.commit()
            #print('新增岗位信息%s'%item['positionId'])
            print('新增岗位信息%s:%s:%s' % (item['positionId'], item['city'], item['positionName']))


    #查询行业信息
    def query_industryfield_result(self):
        info={}
        #查询抓取的行业信息
        result=self.mysql_session.query(Jobtables.industryField).filter(
            #本条可以限制只抓取今日
            # Jobtables.crawl_date==self.date
        ).all()
        #列表生成器 取数据，清除分隔符
        result_list1 = [x[0].split(',')[0] for x in result]
        result_list2 = [x.split('丨')[0] for x in result_list1]
        result_list3 = [x.split('、')[0] for x in result_list2]
        #计数Counter  并限制取条件，根据数据调整
        result_list4 = [x for x in Counter(result_list3).most_common(4)]
        #对数据进行更根据拼接
        data=[{"name":x[0],"value":x[1]} for x in result_list4 ]
        #数据切割，限制个数，优化显示，减低不必要的数据资源占用
        data=data[0:5]
        #生成x轴 项名称
        name_list=[name['name'] for name in data]
        #数据和x轴项名称 打包数据到info
        info['x_name']=name_list
        info['data'] = data
        # 返回数据列表
        return info

    #查询薪资情况，折线图**
    def query_salary_result(self):
        info = {}
        keys=["c++", "java", "web", "python"]
        data={}
        #查找"c++", "java", "web", "python" 薪资情况
        for key in keys:
            #查找关键字的数据记录
            result = self.mysql_session.query(Jobtables.salary).filter(
                # 模糊搜索关键字
                 Jobtables.positionName.like("%"+key+"%")
            ).all()
            # 取出数据存入列表
            result_list1 = [x[0] for x in result]
            # 计数Counter  并限制取条件，根据数据调整
            result_list2 = [x for x in Counter(result_list1).most_common(30)]
            # 对数据进行更根据拼接
            result_list3=[{"name": x[0], "value": x[1]} for x in result_list2]
            #加入关键字数据
            data[key]=result_list3
        # 生成x轴 项名称
        name_list=[name['name'] for name in data['java']]
        # 数据和x轴项名称 打包数据到info
        info['x_name'] = name_list
        info['data']=data
        #返回数据
        return info

    #查询工作年限情况
    def query_workYear_result(self):
        info = {}
        # 查询抓取的工作年限信息
        result = self.mysql_session.query(Jobtables.workYear).filter(
            # 本条可以限制只抓取今日
            # Jobtables.crawl_date==self.date
        ).all()
        # 取出数据存入列表
        result_list1 = [x[0] for x in result]
        # 计数Counter  并限制取条件，根据数据调整
        result_list2 = [x for x in Counter(result_list1).most_common(5)]
        # 对数据进行更根据拼接
        data = [{"name": x[0], "value": x[1]} for x in result_list2]
        # 数据切割，限制个数，优化显示，减低不必要的数据资源占用
        data = data[0:6]
        # 生成x轴 项名称
        name_list = [name['name'] for name in data]
        # 数据和x轴项名称 打包数据到info
        info['x_name'] = name_list
        info['data'] = data
        # 返回数据列表
        return info

    #查询学历信息
    def query_education_resukt(self):
        info = {}
        # 查询抓取的学历信息
        result = self.mysql_session.query(Jobtables.education).filter(
            # 本条可以限制只抓取今日
            # Jobtables.crawl_date==self.date
        ).all()
        # 取出数据存入列表
        result_list1 = [x[0] for x in result]
        # 计数Counter  并限制取条件，根据数据调整
        result_list2 = [x for x in Counter(result_list1).most_common(5)]
        # 对数据进行更根据拼接
        data = [{"name": x[0], "value": x[1]} for x in result_list2]
        # 生成x轴 项名称
        name_list = [name['name'] for name in data]
        # 数据和x轴项名称 打包数据到info
        info['x_name'] = name_list
        info['data'] = data
        # 返回数据列表
        return info

    #岗位发布数量 positionName
    def query_job_result(self):
        info = {}
        keys = ["c++", "java", "web", "python","大数据"]
        data = []
        # 查找"c++", "java", "web", "python" 岗位发布数量
        for key in keys:
            # 查找关键字的数据记录
            result = self.mysql_session.query(Jobtables.positionName).filter(
                # 模糊搜索关键字
                Jobtables.positionName.like("%" + key + "%")
            ).all()


            # 取出数据存入列表
            result_list1 = [x[0] for x in result]
            n=len(result)
            data.append((n,key))
        result_sort = sorted(data)
        result_sort.reverse()
        data=[]
        # 对数据进行更根据拼接
        data = [{"name": x[1], "value": x[0]} for x in result_sort]
        name_list = [name['name'] for name in data ]
        # 数据和x轴项名称 打包数据到info
        info['x_name'] = name_list
        info['data'] = data
        # 返回数据列表
        return info




    #根据城市计数
    def query_city_result(self):
        info = {}
        # 查询抓取的城市信息
        result = self.mysql_session.query(Jobtables.city).filter(
            # 本条可以限制只抓取今日
            # Jobtables.crawl_date==self.date
        ).all()
        # 取出数据存入列表
        result_list1 = [x[0] for x in result]
        # 计数Counter  并限制取条件，根据数据调整
        result_list2 = [x for x in Counter(result_list1).most_common(50)]
        # 对数据进行更根据拼接
        data = [{"name": x[0], "value": x[1]} for x in result_list2]
        # 生成x轴 项名称
        name_list = [name['name'] for name in data]
        # 数据和x轴项名称 打包数据到info
        info['x_name'] = name_list
        info['data'] = data
        # 返回数据列表
        return info


    #融资情况
    def query_financestage_result(self):
        info = {}
        # 查询抓取的融资信息
        result = self.mysql_session.query(Jobtables.financeStage).filter(
            # 本条可以限制只抓取今日
            # Jobtables.crawl_date==self.date
        ).all()
        # 取出数据存入列表
        result_list1 = [x[0] for x in result]
        # 计数Counter  并限制取条件，根据数据调整
        result_list2 = [x for x in Counter(result_list1).most_common(4)]
        # 对数据进行更根据拼接
        data = [{"name": x[0], "value": x[1]} for x in result_list2]
        # 生成x轴 项名称
        name_list = [name['name'] for name in data]
        # 数据和x轴项名称 打包数据到info
        info['x_name'] = name_list
        info['data'] = data
        # 返回数据列表
        return info


    #公司规模
    def query_companysize_result(self):
        info = {}
        # 查询抓取的公司规模信息
        result = self.mysql_session.query(Jobtables.companySize).filter(
            # 本条可以限制只抓取今日
            # Jobtables.crawl_date==self.date
        ).all()
        # 取出数据存入列表
        result_list1 = [x[0] for x in result]
        # 计数Counter  并限制取条件，根据数据调整
        result_list2 = [x for x in Counter(result_list1).most_common(4)]
        # 对数据进行更根据拼接
        data = [{"name": x[0], "value": x[1]} for x in result_list2]
        # 生成x轴 项名称
        name_list = [name['name'] for name in data]
        # 数据和x轴项名称 打包数据到info
        info['x_name'] = name_list
        info['data'] = data
        # 返回数据列表
        return info

    #任职情况
    def query_jobNature_result(self):
        info = {}
        # 查询抓取的行业信息
        result = self.mysql_session.query(Jobtables.jobNature).filter(
            # 本条可以限制只抓取今日
            # Jobtables.crawl_date==self.date
        ).all()
        # 取出数据存入列表
        result_list1 = [x[0] for x in result]
        # 计数Counter  并限制取条件，根据数据调整
        result_list2 = [x for x in Counter(result_list1).most_common(3)]
        # 对数据进行更根据拼接
        data = [{"name": x[0], "value": x[1]} for x in result_list2]
        # 生成x轴 项名称
        name_list = [name['name'] for name in data]
        # 数据和x轴项名称 打包数据到info
        info['x_name'] = name_list
        info['data'] = data
        #返回数据列表
        return info

    #抓取数量
    def count_result(self):
        info={}
        info['all_count'] = self.mysql_session.query(Jobtables).count()
        info['today_count'] = self.mysql_session.query(Jobtables).filter(Jobtables.crawl_date == self.date).count()
        return info

job_mysql=HandleData()
job_mysql.query_job_result()