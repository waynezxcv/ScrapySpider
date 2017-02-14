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




#ifndef VectorList_hpp
#define VectorList_hpp

#include <stdio.h>
#include <vector>
#include "LinearList.hpp"




#pragma mark - Vector实现线性表

namespace LWTL {
    
    template <typename T>
    class VectorList : public LinearList<T> {
        
    public:
        
        //迭代器
        typedef typename std::vector<T>::iterator iterator;
        
        iterator begin() {
            return elements -> begin();
        }
        
        iterator end() {
            return elements -> end();
        }
        
        int capacity() const {
            return elements -> capacity();
        }
        
        //构造函数
        VectorList(int initialCapacity) {
            if (initialCapacity < 0) {
                throw IllegalParameterValue("initail capacity must be > 0");
            }
            elements = new std::vector<T>();
            elements -> reserve (initialCapacity);
        }
        
        
        VectorList() : ListSize(0) , elements(new std::vector<T> ()) {
        }
        
        //拷贝构造函数
        VectorList(const VectorList<T>& rhs) {
            ListSize = rhs.ListSize;
            elements = new std::vector<T> (*rhs.elements);
        }
        
        //拷贝赋值运算符
        VectorList* operator = (const VectorList<T>& rhs) {
            if (rhs == this) {
                return *this;
            }
            
            ListSize = rhs.ListSize;
            delete elements;
            elements = new std::vector<T> (*rhs.elements);
            return *this;
        }
        
        //析构函数
        ~VectorList () override {
            elements -> clear();
            delete elements;
        }
        
        //确定线性表是否为空
        bool empty() const override{
            return ListSize == 0;
        }
        
        //确定线性表长度
        int size() const override{
            return ListSize;
        };
        
        //按一个给定的索引查找一个元素
        T& get(const int& index) const override{
            checkList(index);
            return (*elements)[index];
        }
        
        //按一个给定的元素查找他的索引
        int indexOf(const T& element) const override {
            
            //std::find :如果找到则返回该迭代器，否则返回迭代器last 。[first,last)
            auto theIndex = std::find(elements -> begin(),
                                      elements -> end(),
                                      element);
            
            
            if (*theIndex == ListSize) {
                return -1;
            }
            
            
            return *theIndex;
        }
        
        //按一个给定索引删除一个元素
        void erase(const int& index) override {
            checkList(index);
            elements -> erase(begin() + index);
        }
        
        //按一个给定索引插入一个元素
        void insert( const int& index,const T& element) override {
            if (index < 0 || index > ListSize) {
                throw IllegalParameterValue("the index must between [0,ListSize]");
            }
            elements -> insert(begin() + index,element);
        }
        
        
        //把线性表插入输出流
        void output(std::ostream& out) const override {
            
        }
        
    protected:
        
        void checkList (const int& theIndex ) const {
            if (theIndex < 0 || theIndex >= ListSize) {
                throw IllegalParameterValue("the index must between [0,ListSize)");
            }
        }
        
        
        int ListSize;
        std::vector<T>* elements;
    };
    
}


#endif /* VectorList_hpp */
