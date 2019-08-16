# -*- coding: utf-8 -*-
# @Author: Vincent Vic
# @Date:   2019-08-6 15:14:46
# @Last Modified by:   Vincent Vic
# @Last Modified time: 2019-08-14 20:11:29
# @function:数据抓取

import json             #解析数据使用
import re               #四则运算
import time             #时间
import requests         #请求
import multiprocessing  #多进程
from Job_spider.handle_insert_data import job_mysql  #操作数据库定义的对象

#抓取数据使用
class HandleLagou(object):
    def __init__(self):
        #使用session保存cookies信息
        self.lagou_session=requests.session()
        #头结构设置
        self.header={
            #抓包中获取  User-Agent关键
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:68.0) Gecko/20100101 Firefox/68.0'
        }
        #城市列表初始化
        self.city_list=""
        #城市初始化
        self.key=""

    #获取全国城市列表方法
    def handle_city(self):
        #正则表达式设置
        city_search=re.compile(r'www\.lagou\.com\/.*\/">(.*?)<\/a>')
        #拉钩网全国城市的urk
        city_url="https://www.lagou.com/jobs/allCity.html"
        #调用获取请求，获取城市网页信息
        city_result=self.handle_request(method="GET",url=city_url)
        #使用正则表达式获取城市列表
        self.city_list=city_search.findall(city_result)
        #清除cookies 访问信息
        self.lagou_session.cookies.clear()

    def handle_city_job(self, city):
        #搜索指定工作和城市的岗位信息
        first_request_url="https://www.lagou.com/jobs/list_%s"% self.key + "?px=default&city=%s"%city
        #获取信息搜索信息
        first_response=self.handle_request(method="GET",url=first_request_url)
        #正则表达式查找匹配设置
        total_page_search=re.compile(r'class="span\stotalNum">(\d+)</span>')
        try:
            #正则表达式查找获取的总页数
            tatal_page=total_page_search.search(first_response).group(1)
        except: #由于没岗位信息造成exceptio
            return
        else:
            #循环获取每页岗位信息
            for i in range(1,int(tatal_page)+1):
                #post请求需要提交页面以及搜索关键字
                data={
                    "pn":i,
                    "kd":self.key
                }
                #请求post url 抓包获取
                page_url="https://www.lagou.com/jobs/positionAjax.json?px=default&city=%s&needAddtionalResult=false"%city
                #referer url   拼接关键字和城市
                referer_url="https://www.lagou.com/jobs/list_%s"% self.key + "?px=default&city=%s"%city
                #referer的URL需要进行encode
                self.header['Referer']=referer_url.encode()
                #获取post请求
                response=self.handle_request(method="POST",url=page_url,data=data,info=city)
                #json解码
                lagou_data=json.loads(response)
                #取出工作岗位数据  json.com 网站分析数据得出结论
                job_list=lagou_data['content']['positionResult']['result']
                #存入数据库
                for job in job_list:
                    job_mysql.insert_item(job)

    def handle_request(self,method,url,data=None,info=None):
        while True:
            #阿布云代理   地址                    证书               密钥                代理地址          端口
            proxyinfo="http://%s:%s@%s:%s" % ('H8035GA3C2PF6ERD','7D4496EEDA850F5D','http-dyn.abuyun.com','9020')
            #代理设置
            proxy={
                "http":proxyinfo,
                "https":proxyinfo
            }

            try:
                #请求
                if method =="GET":
                    response=self.lagou_session.get(url=url,headers=self.header,proxies=proxy,timeout=6)
                elif method=="POST":
                    response=self.lagou_session.post(url=url,headers=self.header,data=data,proxies=proxy,timeout=6)
            except:
                # 清除cookies信息
                self.lagou_session.cookies.clear()
                # 重新获取cookies信息
                first_request_url = "https://www.lagou.com/jobs/list_%s"% self.key + "?px=default&city=%s" % info
                self.handle_request(method="GET", url=first_request_url)
                time.sleep(10)
                continue
            #设置获取编码
            response.encoding = "utf-8"
            if '频繁' in response.text:
                print(response.text)
                #清除cookies信息
                self.lagou_session.cookies.clear()
                #重新获取cookies信息
                first_request_url="https://www.lagou.com/jobs/list_%s"% lagou.key + "?px=default&city=%s" % info
                self.handle_request(method="GET", url=first_request_url)
                time.sleep(10)
                continue
            return response.text

if __name__ =='__main__':
    #查找实例化
    lagou=HandleLagou()
    #查找关键字列表
    key_listy = [  "python", "c++","python","大数据","web","java","web", "web", "python"]
    for keys in key_listy:
        #获取城市列表
        lagou.handle_city()
        #创建进程池，加速抓数据
        pool=multiprocessing.Pool(2)
        #设置查找关键字
        print(lagou.city_list)
        lagou.key = keys
        for city in lagou.city_list:
            if city!= None :
                #查找加入进程
                pool.apply_async(lagou.handle_city_job,args=(city,))
        #关闭进程池
        pool.close()
        #加入
        pool.join()