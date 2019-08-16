# -*- coding: utf-8 -*-
# @Author: Vincent Vic
# @Date:   2019-08-6 15:14:46
# @Last Modified by:   Vincent Vic
# @Last Modified time: 2019-08-14 20:11:29
# @function:服务器端，发布更新信息

from flask import Flask, render_template, jsonify
from Job_spider.handle_insert_data import job_mysql
#flask实例化
app=Flask(__name__)

#绑定路由
@app.route("/",methods=['GET','POST'])
def Job():
    # 库内数据总量，今日抓取量
    result = job_mysql.count_result()
    return render_template('index.html', result=result)

@app.route('/get_echart_data')
def get_echart_data():
    info={}

    # 存储行业信息数据
    info['echart_1']=job_mysql.query_industryfield_result()

    # 存储岗位发布数量数据，折线图
    info['echart_2'] = job_mysql.query_job_result()

    # 存储薪资情况数据
    info['echart_4'] = job_mysql.query_salary_result()

    # 存储融资情况数据
    info['echart_31'] = job_mysql.query_financestage_result()

    #存储公司规模数据
    info['echart_32'] = job_mysql.query_companysize_result()

    #存储岗位要求数据
    info['echart_33'] = job_mysql.query_jobNature_result()

    #存储工作年限情况数据
    info['echart_5'] = job_mysql.query_workYear_result()

    #存储学历数据
    info['echart_6'] = job_mysql.query_education_resukt()

    #存储根据城市计数，给地图绘制点
    info['map'] = job_mysql.query_city_result()

    info['total']=job_mysql.count_result()

    return jsonify(info)



if __name__ =="__main__":
    app.run(debug=True,host="127.0.0.1",port=80)