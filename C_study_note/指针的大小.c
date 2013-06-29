# include <stdio.h>
 
int main ()
{
    int a=8;
    char ch = 'j';
    double h = 102.0152;
    int * p =&a;
    char * q = &ch;
    double * r = & h;
    
    printf ("%d   %d   %d\n",sizeof(a),sizeof(char),sizeof(h)); 
    printf ("%d  %d  %d\n",sizeof(p),sizeof(q),sizeof(r));
    /*sizeof()的用法：sizeof（数组类型或变量）
    功能：计算（）内的数据类型或变量所占得字节数，并返回*/
    system ("pause");
    return 0;
}
/*
   指针变量只保存数据类型首字节的编号，只占4个字节 
  指针变量类型说明了指针指向的变量的具体长度
  指针变量存储的是变量首字节的变量编号，给变量的大小无关 
*/
