# -*- coding: utf-8 -*-

# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: http://doc.scrapy.org/en/latest/topics/item-pipeline.html



from scrapy import signals
import mysql.connector
import json

class CocoachinaPipeline(object):
    def __init__(self):  
        self.conn = mysql.connector.connect(host = 'rds5r1sifk46m17i665co.mysql.rds.aliyuncs.com',port = '3306',user='waynezxcv', password='xxxx', database='cocoachina', use_unicode=True)
        self.cursor = self.conn.cursor()

    def process_item(self, item, spider):  
        articleUrl = item['articleUrl']
        title = item['title']
        date = item['date']
        editor = item['editor']
        classify = item['classify']
        source = item['source']
        sourceUrl = item['sourceUrl']
        contents = json.dumps(item['content'])
        self.cursor.execute('insert into t_article (articleUrl,title,date,editor,classify,source,sourceUrl,contents) values (%s, %s, %s, %s, %s, %s, %s, %s)',[articleUrl,title,date,editor,classify,sourceUrl,sourceUrl,contents])
        self.conn.commit()
        return item

    def spider_closed(self, spider):  
        self.cursor.close()	
