# -*- coding: utf-8 -*-
# @Author: Vincent Vic
# @Date:   2019-08-14 15:14:46
# @Last Modified by:   Administrator
# @Last Modified time: 2019-08-16 03:19:14
# @function:服务器信息的设置

class Informations:
    def __init__(self):
        '''self.username="root"
        self.password="111111"
        self.ip_address="192.168.56.130"
        self.port="3306"
        self.SQLDataName="Job_Big_Data"'''
        self.username = "root"  # 数据库用户名
        self.password = "123456"  # 数据库密码
        self.ip_address = "127.0.0.1"  # 数据库ip或者网址
        self.port = "3306"  # 端口
        self.SQLDataName = " Job_Big_Data"  # 数据库名称
    def getUserName(self):
        return self.username

    def getPassword(self):
        return self.password

    def getIpAddress(self):
        return self.ip_address

    def getPort(self):
        return self.port

    def getSQLDataName(self):
        return self.SQLDataName

info=Informations()