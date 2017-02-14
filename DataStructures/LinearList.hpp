/*
 Copyright (c) 2017 waynezxcv <liuweiself@126.com>
 
 https://github.com/waynezxcv/Playground
 
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */




#ifndef LinearList_hpp
#define LinearList_hpp

#include <iostream>
#include <ostream>
#include "IllegalParameterValue.hpp"


/******************** 线性表 *******************/

/*
 ADT

 线性表应该实施下列操作：
 创建一个线性表
 撤销一个线性表
 确定线性表是否为空
 确定线性表长度
 按一个给定的索引查找一个元素
 按一个给定的元素查找他的索引
 按一个给定的索引删除一个元素
 按一个给定的索引插入一个元素
 从左至右依次输出线性表元素

 */


#pragma mark - 线性表的抽象类

namespace LWTL {


    template <typename T>
    class LinearList {
    public:
        virtual ~LinearList() {};
        virtual bool empty() const = 0;//确定线性表是否为空
        virtual int size() const = 0;//确定线性表长度
        virtual T& get(const int& index) const = 0;//按一个给定的索引查找一个元素
        virtual int indexOf(const T& element) const = 0;//按一个给定的元素查找他的索引
        virtual void erase(const int& index) = 0;//按一个给定索引删除一个元素
        virtual void insert( const int& index,const T& element) = 0;//按一个给定索引插入一个元素
        virtual void output(std::ostream& out) const = 0;//把线性表插入输出流
    };

}


#endif /* LinearList_hpp */
