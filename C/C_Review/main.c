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

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/file.h>




void inplace_swap(int* x,int* y);
void sum_swap(int* x,int* y);
void fileCopy(FILE* ifp,FILE* ofp);

void pointerAndArray ();
void optionTest();
void unixAPI();
void IO_API();




int main(int argc, const char * argv[]) {
    
    return 0;
}



/******************************************* Pointer & Array **************************************/

void pointerAndArray () {
    
    int arr [5] = {1,2,3,4,5};
    
    //数组名在大多数情况下，会被隐式转换成 “数组第一个元素指针的右值”。
    //除了：
    //1.sizeof运算时
    //sizeof(arr) != sizeof(int *)
    size_t s = sizeof(arr);//得到的是整个数组所有元素的大小
    printf("sizeof(arr) : %zu\n",s);//结果是sizeof(int) * 5
    
    
    //2.取地址时
    //对数组名取地址得到指针进行加减，增减字节数是sizeof(arr)
    //即返回的是指向的是数组的指针，而非初始元素的指针
    //&arr是一个指向 有5个int类型元素数组的指针。
    
    int (*ap) [5] = &arr;//指向数组的指针
    int* ip = arr;//指向数组第一个元素的指针(&arr[0])
    
    printf("(&arr) : %p\n",ap);
    printf("(&arr + 1) : %p\n",ap + 1);//结果是在数组第一个元素的地址的基础上增加20个字节 sizeof(int) * 5;
    printf("(arr + 1) : %p\n",arr + 1);//结果是在第一个元素的地址的基础上增加4个字节（sizeof(int)）;
    
    //3.用字符串常量进行赋值的时候
    
    char ch [6];
    
    ch = "hello";
    
    printf("ch : %s \n",ch);
    
    
    
    //下标运算符是语法糖. arr[i] 等同于 *(arr + i)
    //由此:arr[i] = *(arr + i) = *(i + arr) = i[arr]
    //4[arr] = ?  (arr[4])
    
    printf("4[arr] : %d\n",4[arr]);
    
}


/***************************************** Bit ***************************************************************/

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



//或 | 添加选项 。。
//与非 &= ~(xxx) 去除选项 。。
//与 & 判断选项


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


/***************************************** I/O ***************************************************************/


void unixAPI() {
    
    //#include <unistd.h>
    
    //输入/输出、文件系统、存储分配。
    
    //1.文件描述符
    //文件描述符：在UNIX操作系统中，所有的外围设备（包括键盘和显示器），都被看做是文件系统中的文件，因此，所有的输入/输出都要通过读文件和写文件完成
    //通常情况下，要读写文件之前，必须先将这个意图通知系统，该过程称为打开文件。如果是写一个文件，则可能需要先创建该文件，也可能需要丢弃该文件中原先已存在的内容
    //系统检查你的权利，如果一切正常，操作系统将向程序返回一个非负整数，该整数为文件描述符。
    //任何时候，对文件的输入输出都是通过文件描述符，而不是通过文件名。
    //类似标准库中的文件指针(FILE *)或MS-DOS中的文件句柄。
    //UNIX默认打开三个文件，对应0、1、2，分别表示标准输入、标准输出、标准错误
    
    
    //2.低级I/O --- read和write
    //将标准输入复制到标准输出
    //    char buff [1024];
    //    int n;
    //    while ((n == read(0, buff, 1024)) > 0) {
    //        write(1, buff, n);
    //    }
    
    //除了默认的标准输入、标准输出、标准错误文件外，其他文件都需要在 读写之前显示的打开。
    //系统调用open和creat函数实现该功能
    //open类似标准库fopen函数，前者 返回文件描述符，后者返回文件指针。#include <fcntl.h> #include <sys/file.h>
    
    
    //第一参数文件路径，第二个参数说明以何种方式打开文件，第三个参数指定权限
    /*
     #define	O_RDONLY	0x0000 只读
     #define	O_WRONLY	0x0001 只写
     #define	O_RDWR		0x0002 读写
     #define	O_ACCMODE	0x0003
     */
    //    int fd = open("/Users/liuwei/Desktop/Playground/I\:O/O/testfile", O_RDWR,0);
    
    //如果用open打开一个不存在的文件，将导致错误。
    //可以使用creat系统调用创建新文件或覆盖已有文件。
    //close关闭文件，并释放文件描述符，以供其他文件使用。
    //unlink将文件删除，对应标准库中的remove
    
    
    //3.随机访问lseek
    //可以再文件中任意移动位置而不实际读写任何数据
    
    
}


void IO_API() {
    
    //如何将用户需要使用的文件的外部名同读取数据的语句关联起来？
    //使用fopen打开该文件
    //fopen()函数返回一个指向FILE结构体的指针，文件指针。
    //FILE* fp = fopen("文件名", "访问模式");
    //访问模式包括:"r"读，"w"写，"a"追加。某些西东还区分文本文件和二进制文件,对二进制文件的访问需要在模式字符串中增加字符"b"
    //启动一个C语言程序时，操作系统环境负责打开三个文件，并将这3个文件指针提供给改程序。
    //这3个文件分别是：标准输入，标准输出，标准错误。
    //对应的文件指针分别是stdin,stdout,stderr
    
    FILE* ifp = fopen("/Users/liuwei/Desktop/Playground/C_Review/testfile","r");
    FILE* ofp = fopen("/Users/liuwei/Desktop/Playground/C_Review/testfile_copy", "w");//打开一个不存在文件用于写，该文件将会被创建
    
    fileCopy(ifp, ofp);
    
    
    //fclose，断开由fopen函数建立的文件指针和外部名之间的连接，并释放文件指针供其他文件使用。
    fclose(ifp);
    fclose(ofp);
}

//将文件ifp复制到文件ofp
void fileCopy(FILE* ifp,FILE* ofp) {
    int c;
    //getc函数从文件返回fp指向的输入流的下一个字符
    while ((c = getc(ifp)) != EOF) {
        
        //putc函数是一个输出函数，该函数将字符c写入到fp指向的文件中，并返回写入的字符
        putc(c, ofp);
    }
}





