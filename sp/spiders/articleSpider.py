# -*- coding: utf-8 -*-


import scrapy
from scrapy.selector import Selector
from scrapy.contrib.spiders import CrawlSpider, Rule
from scrapy.http import Request



class articleSpider(scrapy.Spider):
    name = "articleSpider"
    allowed_domains = ["cocoachina.com"]
    start_urls = [
        "http://www.cocoachina.com/swift/20151223/14774.html",
    ]
    def parse(self, response):
    	items = []
		#标题
    	title = response.xpath('//div[@class="detail-main"]/h2/text()').extract()[0]
    	items.append(title)
    	#日期
    	date = response.xpath('//div[@class="p-ico clearfix"]/div/span[@class="ml0"]/text()').extract()[0]
    	items.append(date)
    	#编辑
    	edit = response.xpath('//div[@class="p-ico clearfix"]/div/span/a/text()').extract()[0]
    	items.append(edit)
    	#分类
    	classify = response.xpath('//div[@class="p-ico clearfix"]/div/span/a/text()').extract()[1]
    	items.append(classify)
    	#来源
    	source = response.xpath('//div[@class="p-ico clearfix"]/div/span/a/text()').extract()[2]
    	srouceUrl = response.xpath('//div[@class="p-ico clearfix"]/div/span/a/@href').extract()[2]
    	items.append(source)
    	items.append(srouceUrl)
    	#正文
        for detailSelector in response.xpath('//div[@id="detailbody"]/p'):
        	#正文中的文字
			if len(detailSelector.xpath('text()')) != 0:
				items.append(detailSelector.xpath('text()').extract()[0])
			#正文中的图片
			if len(detailSelector.xpath('img/@src')) != 0:
				items.append(detailSelector.xpath('img/@src').extract()[0])
			#正文中的链接
			if len(detailSelector.xpath('a/@href')) != 0:
				items.append(detailSelector.xpath('a/text()').extract()[0])
				items.append(detailSelector.xpath('a/@href').extract()[0])
	for i in range(0,len(items)):
		print "%s ........... %s" % (items[i],i)       	