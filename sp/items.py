# -*- coding: utf-8 -*-

# Define here the models for your scraped items
#
# See documentation in:
# http://doc.scrapy.org/en/latest/topics/items.html

import scrapy


class CocoachinaItem(scrapy.Item):
    # define the fields for your item here like:
    # name = scrapy.Field()
	articleUrl =scrapy.Field()
	title = scrapy.Field()
	date = scrapy.Field()
	editor = scrapy.Field()
	classify = scrapy.Field()
	source = scrapy.Field()
	sourceUrl = scrapy.Field()
	content = scrapy.Field()