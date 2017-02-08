//
//  main.c
//  Bit
//
//  Created by 刘微 on 2017/2/8.
//  Copyright © 2017年 WayneInc. All rights reserved.
//

#include <stdio.h>


void inplace_swap(int* x,int* y);
void sum_swap(int* x,int* y);




//按位与运算通常用来对某些位清 0，或者保留某些位。
//按位或运算可以用来将某些位置 1，或者保留某些位。
//按位异或运算可以用来将某些二进制位反转。
//左移运算符<<用来把操作数的各个二进制位全部左移若干位，高位丢弃，低位补0。
//右移运算符>>用来把操作数的各个二进制位全部右移若干位，低位丢弃，高位补 0 或 1。如果数据的最高位是 0，那么就补 0；如果最高位是 1，那么就补 1。


/*使用位域压缩内存占用*/
//在结构体定义时，我们可以指定某个成员变量所占用的二进制位数（Bit），这就是位域。

struct Bs {
    unsigned a : 1;
    unsigned b : 22;//位域的宽度不能超过它所依附的数据类型的长度。 ：右边的值不能超过unsigned的最大位数 4(字节) * 8 (bit) = 32
    unsigned : 2;//无名位域。无名位域一般用来作填充或者调整成员位置。因为没有名称，无名位域不能使用。
    unsigned d : 1;
} bs;




/*不借助中间变量交换两个变量的值*/
//使用异或交换变量
void inplace_swap(int* x,int* y) {
    *y = *x ^ *y;
    *x = *x ^ *y;
    *y = *x ^ *y;
}


//使用求和的方式交换变量
void sum_swap(int* x,int* y) {
    *x = *x + *y;
    *y = *x - *y;
    *x = *x - *y;
}

/*************************/


/*使用位运算实现可多选的枚举类型*/
typedef enum {
    Option1 = 1 << 0, //0001
    Option2 = 1 << 1, //0010
    Option3 = 1 << 2, //0100
    Option4 = 1 << 3, //1000
} Option;



void optionTest() {
    Option o;
    o = Option1 | Option2;//  0001 | 0010 => 0011;  同时选择Option1和Option2
    o |= Option3;//增加Option3选项  0011 | 0100 => 0111
    o &= ~Option2;//去除Option2选项 0111 & ~0010 => 0111 & 1101 => 0101
    o = o & ~Option1;//去除Option1选项 0101 & ~0001 => 0101 & 1110 => 0100
    o = o | Option4;//增加Option4选项 0100 | 1000 => 1100 (12)
    
    //判断o中是否选择了Option1,1100 & 0001 => 0000 false
    if (o & Option1) {
        printf("selected option1\n");
    } else {
        printf("not selected option1\n");
    }
    
    //判断o中是否选择了Option2, 1100 & 0010 => 0000 false
    if (o & Option2) {
        printf("selected option2\n");
    } else {
        printf("not selected option2\n");
    }
    
    
    //判断o中是否选择了Option3 ,1100 & 0100 => 0100 true
    if (o & Option3) {
        printf("selected option3\n");
    } else {
        printf("not selected option3\n");
    }
    
    //判断o中是否选择了Option4 1100 & 1000 => 1000 true
    if (o & Option4) {
        printf("selected option4\n");
    } else {
        printf("not selected option4\n");
    }
}

int main(int argc, const char * argv[]) {
    
    
    
    return 0;
}





