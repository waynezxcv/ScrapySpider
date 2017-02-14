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
#ifndef ArrayList_hpp
#define ArrayList_hpp

#include <stdio.h>
#include "LinearList.hpp"

#pragma mark - 用数组描述的线性表(No STL)

namespace LWTL {

    template <typename T>
    class ArrayList : public LinearList<T> {

    public:
        //ArrayList<T>::iterator 迭代器
        class iterator {
        public:

            typedef std::bidirectional_iterator_tag iteraotr_category;
            typedef ptrdiff_t difference_type;
            typedef T value_type;
            typedef T* pointer;
            typedef T& reference;

            //构造函数
            iterator(T* thePosition = 0) {
                position = thePosition;
            }

            T& operator *() const {
                return *position;
            }

            T* operator &() const {
                return &(*position);
            }

            //迭代器值增加
            iterator& operator ++ () {//前加  ++ it;
                ++ position;
                return *this;
            }

            iterator operator ++ (int) {//后加 it  ++;
                iterator old = *this;
                ++ position;
                return old;
            }

            //迭代器值减小
            iterator& operator -- () {//前减 -- it;
                -- position;
                return *this;
            }

            iterator operator -- (int) {//后减 it --;
                iterator old = *this;
                -- position;
                return old;
            }

            //是否相等
            bool operator != (const iterator rightIt) const {
                return (position != rightIt.position);
            }

            bool operator == (const iterator rightIt) const {
                return (position == rightIt.position);
            }


        protected:
            T* position;
        };

        iterator begin() {
            return iterator(elements);
        }

        iterator end() {
            return iterator(elements + ListSize);
        }

        //构造函数
        ArrayList(int cap = 10) : capacity(cap) {
            if (capacity < 1) {
                //抛出异常
                throw IllegalParameterValue("initial capcity must be > 0");
            } else {
                elements = new T [capacity];
                arrayLength = capacity;
                ListSize = 0;
            }
        }

        //拷贝构造函数
        ArrayList(const ArrayList<T>& rhs) {
            arrayLength = rhs.arrayLength;
            ListSize = rhs.ListSize;
            elements = new T [arrayLength];
            memcpy(elements, rhs.elements, ListSize *  sizeof(T));
        }


        //重载拷贝赋值运算符
        ArrayList& operator = (const ArrayList<T>& rhs) {

            if (this == &rhs) {
                return *this;
            }
            arrayLength = rhs.arrayLength;
            ListSize = rhs.ListSize;
            delete [] elements;
            elements = new T [arrayLength];
            memcpy(elements, rhs.elements, ListSize *  sizeof(T));
            return *this;
        }

        //析构函数
        ~ArrayList() override {
            delete [] elements;
        };

        //确定线性表是否为空,为空返回true，不为空返回false
        bool empty() const override {
            return ListSize == 0;
        }

        //确定线性表长度
        int size () const override {
            return ListSize;
        }

        //按一个给定的索引查找一个元素
        T& get(const int& index) const override {
            checkIndex(index);
            return  *(elements + index);
        }

        //按一个给定元素查找他的索引
        int indexOf(const T& element) const override {
            for (int i = 0; i < ListSize; i ++) {
                if (element == elements[i]) {
                    return i;
                }
            }
            return -1;
        }

        //按一个给定索引删除一个元素
        void erase(const int& index) override {

            checkIndex(index);
            T t = elements[index];

            //调用析构函数
            t.~T();

            for (int i = index; i  < ListSize - 1; i ++ ) {
                elements[i] = elements[i + 1];
            }

            ListSize --;


            //当ListSize < ArrayLength/4 时，要将数组长度减少到 max{initialCapcity,ArrayLength/2}
            if (ListSize < arrayLength /4 && arrayLength > capacity) {
                int length = capacity >= arrayLength /2 ? capacity : arrayLength/2;
                changeArrayLength1D(elements, arrayLength, length);
                arrayLength = length;
            }
        }

        //按一个给定索引插入一个元素
        void insert(const int& index,const T& t) override {

            //检查索引是否有效
            if (index < 0 || index > ListSize) {
                throw IllegalParameterValue("insert index must be between [0 , listSize)\n");
            }

            auto _insert = [this,index,t] () -> void {
                for (int i = ListSize; i > index; i --) {
                    elements[i] = elements[i - 1];
                }
                elements[index] = t;
                ListSize ++;
            };


            //判断数组容量是否已满
            if (ListSize == arrayLength) {
                //改变数组长度到原来的2倍
                changeArrayLength1D(elements, arrayLength, arrayLength * 2);
                arrayLength *= 2;
                _insert();
            } else {
                _insert();
            }
        }

        //把线性表插入输出流
        void output(std::ostream& out) const override {
            
        }
        
        //重载<<运算符
        //        std::ostream& operator << (std::ostream& out,const ArrayList<T>& x) {
        //            x.output(out);
        //            return out;
        //        }
        
    protected:
        
        T* elements;//存储线性表的数组
        int capacity;
        int arrayLength;//数组的容量
        int ListSize;//线性表的元素个数
        
        
        //检查索引值是否非法
        void checkIndex(const int& index) const {
            //确认索引在0 和 ListSize - 1
            if (index < 0 || index >= ListSize) {
                //抛出异常
                throw IllegalParameterValue("the index must be between [0 , listSize)");
            }
        }
        
        //改变一个一维数组的长度
        void changeArrayLength1D(T*& t,const int& oldLength,const int& newLength) {
            
            if (newLength < 1) {
                //抛出异常
                throw IllegalParameterValue("the length must be > 0");
            }
            
            T* tmp = new T [newLength];
            //将原来的数组元素赋值到新的数组
            memcpy(tmp, t, ListSize * sizeof(T));
            
            //释放原来的数组内存
            delete [] t;
            
            //将t指向新的数组
            t = tmp;
        }
    };
}


#endif /* ArrayList_hpp */
