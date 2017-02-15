# -*- coding: utf-8 -*-

import mysql.connector
import json


conn = mysql.connector.connect(host = 'rds5r1sifk46m17i665c.mysql.rds.aliyuncs.com',port = '3306',user='waynezxcv', password='123456', database='cocoachina', use_unicode=True)
cursor = conn.cursor()
cursor.execute('select * from t_article')
values = cursor.fetchall()

for value in values:
	contents = value["contents"]
	for dic in contents:
		print dic["content"]

cursor.close()
