//
//  VectorList.hpp
//  DataStructures
//
//  Created by 刘微 on 17/2/14.
//  Copyright © 2017年 刘微. All rights reserved.
//

#ifndef VectorList_hpp
#define VectorList_hpp

#include <stdio.h>
#include "LinearList.hpp"
#include <vector>




#pragma mark - Vector实现线性表

namespace LWTL {

    template <typename T>
    class VectorList : public LinearList<T> {
    public:

        class iterator {
        public:
            iterator(const typename std::vector<T>::iterator& it) : position(it) {}

            iterator& operator ++ () {
                position ++ ;
                return *this;
            }

            iterator operator ++ (int) {
                iterator old = *this;
                position ++;
                return old;
            }


            iterator& operator -- () {
                position -- ;
                return *this;
            }

            iterator operator -- (int) {
                iterator old = *this;
                position --;
                return old;
            }

            T* operator & () const {
                return &position;
            }

            T& operator * () const {
                return *position;
            }


            bool operator != (iterator rightIt) const {
                return position != rightIt.position;
            }


            bool operator == (iterator rightIt) const {
                return position == rightIt.position;
            }

            typename std::vector<T>::iterator position;
        };

        iterator begin() {
            return iterator(elements.begin());
        }

        iterator end() {
            return iterator(elements.end());
        }

        //构造函数
        VectorList() : elements(std::vector<T>()) {
            printf("constructor\n");
        }

        //拷贝构造函数
        VectorList(const VectorList<T>& rhs) {
            ListSize = rhs.ListSize;
            elements = rhs.elements;
        }

        //拷贝赋值运算符
        VectorList* operator = (const VectorList<T>& rhs) {
            if (rhs == this) {
                return *this;
            }
            ListSize = rhs.ListSize;
            elements = rhs.elements;
        }

        //析构函数
        ~VectorList () {
            elements.clear();
        }


        //确定线性表是否为空
        bool empty() const {
            return ListSize == 0;
        }

        //确定线性表长度
        int size() const {
            return ListSize;
        };

        //按一个给定的索引查找一个元素
        T& get(const int& index) const {
            checkList(index);
            return elements[index];
        }

        //按一个给定的元素查找他的索引
        int indexOf(const T& element) const {
            int theIndex = (int) std::find(elements.begin(), elements.end(), element);
            if (theIndex == ListSize) {
                return -1;
            }
            return theIndex;
        }

        //按一个给定索引删除一个元素
        void erase(const int& index){
            checkList(index);
            elements.erase(elements.begin() + index);
        }

        //按一个给定索引插入一个元素
        void insert( const int& index,const T& element){
            if (index < 0 || index > ListSize) {
                throw IllegalParameterValue("the index must between [0,ListSize]");
            }
            elements.insert(elements.begin() + index,element);
        }

        //把线性表插入输出流
        void output(std::ostream& out) const {

        }

    protected:

        void checkList (const int& theIndex ) const {
            if (theIndex < 0 || theIndex >= ListSize) {
                throw IllegalParameterValue("the index must between [0,ListSize)");
            }
        }
        
        int ListSize;
        std::vector<T *> elements;
    };
    
}


#endif /* VectorList_hpp */
