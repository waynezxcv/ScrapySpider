# -*- coding: utf-8 -*-


from cocoachina.items import CocoachinaItem
import scrapy
from scrapy.selector import Selector
from scrapy.contrib.spiders import CrawlSpider, Rule
from scrapy.http import Request
import json

class cocoachinaSpider(scrapy.Spider):
    name = "cocoachina"
    allowed_domains = ["cocoachina.com"]
    start_urls = [
        "http://www.cocoachina.com/news/index.php?num=2",
    ]
    url = 'http://www.cocoachina.com/news/index.php?num='
    page = 2
    def parse(self, response):
        for clearfixSelector in response.xpath('//li[@class="clearfix"]'):
            # dateSelector = clearfixSelector.xpath('h6[@class="float-l"]/text()').extract();
            # for date in dateSelector:
               # print "---------------- %s -------------" % date
            for sel in clearfixSelector.xpath('ul/li/a'):
                title = sel.xpath('text()').extract()[0]
                url = sel.xpath('@href').extract()[0]
                # print title,url                
                yield Request(url,callback = self.articleParse)
            self.page = self.page + 1
            yield Request(self.url + '%s' % self.page,callback = self.parse)

    def articleParse(self,response):
        #文章的URL
        articleUrl = response.url
        #标题
        title = response.xpath('//div[@class="detail-main"]/h2/text()').extract()[0]
        #日期
        date = response.xpath('//div[@class="p-ico clearfix"]/div/span[@class="ml0"]/text()').extract()[0]
        #编辑
        editor = response.xpath('//div[@class="p-ico clearfix"]/div/span/a/text()').extract()[0]
        #分类
        classify = response.xpath('//div[@class="p-ico clearfix"]/div/span/a/text()').extract()[1]
        #来源
        source = response.xpath('//div[@class="p-ico clearfix"]/div/span/a/text()').extract()[2]
        #来源URL
        sourceUrl = response.xpath('//div[@class="p-ico clearfix"]/div/span/a/@href').extract()[2]
        #================================================================================#
        item = CocoachinaItem()
        item["articleUrl"] = articleUrl
        item["title"] = title
        item["date"] = date
        item["editor"] = editor
        item["classify"] = classify
        item["source"] = source
        item["sourceUrl"]  = sourceUrl
        #正文
        contents = []
        for detailSelector in response.xpath('//div[@id="detailbody"]/p'):
            #正文中的文字
            if len(detailSelector.xpath('text()')) != 0:
                textDict = {
                    'type':'text',
                    'content':detailSelector.xpath('text()').extract()[0],
                    'url':'',
                }
                contents.append(textDict)
            #正文中的图片
            if len(detailSelector.xpath('img/@src')) != 0:
                imgDict = {
                    'type':'img',
                    'content':'',
                    'url':detailSelector.xpath('img/@src').extract()[0],
                }
                contents.append(imgDict)
            #正文中的链接
            if len(detailSelector.xpath('a/@href')) != 0:
                linkDict = {
                    'type':'link',
                    'content':detailSelector.xpath('a/text()').extract()[0],
                    'url':detailSelector.xpath('a/@href').extract()[0]
                }
                contents.append(linkDict)
        item["content"] = contents
        yield item


      