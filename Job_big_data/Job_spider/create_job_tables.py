# -*- coding: utf-8 -*-
# @Author: Vincent Vic
# @Date:   2019-08-6 17:28:36
# @Last Modified by:   Vincent Vic
# @Last Modified time: 2019-08-14 20:11:29
# @function:数据表定义以及创建，连接

from sqlalchemy import create_engine, Integer, Float,String
from sqlalchemy.orm import sessionmaker
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy import Column
from Job_spider.information import info

#创建数据库连接  使用需要设置mysql服务器信息  服务器用户名 ：密码 @ IP地址：端口号/数据库名称
engine=create_engine("mysql+pymysql://"+info.getUserName()+":"+info.getPassword()+"@"+info.getIpAddress()+":"+info.getPort()+"/"+info.getSQLDataName()+"?charset=utf8")

#操作数据库
Session=sessionmaker(bind=engine)

#声明一个基类
Base=declarative_base()

#数据类
class Jobtables(Base):
    #表名称
    __tablename__ = 'job_datas'
    #id,设置为主键和自动增长
    id = Column(Integer,primary_key=True,autoincrement=True)
    #岗位ID,非空字段
    positionID = Column(Integer,nullable=True)
    # 经度
    longitude = Column(Float, nullable=False)
    # 纬度
    latitude = Column(Float, nullable=False)
    # 岗位名称
    positionName = Column(String(length=50), nullable=False)
    # 工作年限
    workYear = Column(String(length=20), nullable=False)
    # 学历
    education = Column(String(length=20), nullable=False)
    # 岗位性质
    jobNature = Column(String(length=20), nullable=True)
    # 公司类型
    financeStage = Column(String(length=30), nullable=True)
    # 公司规模
    companySize = Column(String(length=30), nullable=True)
    # 业务方向
    industryField = Column(String(length=30), nullable=True)
    # 所在城市
    city = Column(String(length=10), nullable=False)
    # 岗位标签
    positionAdvantage = Column(String(length=200), nullable=True)
    # 公司简称
    companyShortName = Column(String(length=50), nullable=True)
    # 公司全称
    companyFullName = Column(String(length=200), nullable=True)
    # 公司所在区
    district = Column(String(length=20), nullable=True)
    # 公司福利标签
    companyLabelList = Column(String(length=200), nullable=True)
    # 工资
    salary = Column(String(length=20), nullable=False)
    # 抓取日期
    crawl_date = Column(String(length=20), nullable=False)

if __name__ == '__main__':
    #创建数据表
    Jobtables.metadata.create_all(engine)