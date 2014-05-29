/*malloc的使用
malloc是cmemory(内存) allocste(分配)的缩写*/
# include <stdio.h>
# include <malloc.h>
int main (void)
{
    int a = 5;//分配了4个字节，静态分配 。
    int * p = (int *)malloc(4);//一共分配了8个字节，p变量占4个，p指向的内存（malloc分配的）4个。 
      /*1.要使用malloc函数，必须添加malloc.h这个头文件
        2.malloc函数只有一个形参并且形参是整形
        3.（）中的4表示请求系统为本程序分配4个字节
        4.malloc函数只能返回第一个字节的地址 
        5.(int *)表示把malloc分配的内存空间强制转换成int形式的内存地址 
          例：(char *)malloc(200),内含200个char变量。 (int *)malloc(200)内含50个int变量 
        6.p本身所占的内存是静态的，p指向的内存（malloc分配的）是动态的 
      */
    int *q = (int *)calloc(1,4);
    printf ("%#X哈哈%d\n",p,*p) ; 
    printf ("%#X;)%d\n",q,*q);
    
    *q = 54;
    *p = 45;
    printf ("%#X哈哈%d\n",p,*p);//输出结果：0X380F18哈哈45
    printf ("%#X;)%d\n",q,*q);
    
    free(p);//表示把p所指向的（malloc分配的）内存给释放掉了。p本身的内存是静态的，并没有释放，
            //p本身的内存只有在函数运行完时内存自动释放。
            
    
    printf ("%#X嘻嘻%d\n",p,*p); //输出结果：0X380F18嘻嘻3673984（垃圾值） *p输出是垃圾值，是因为p所指向的内存被释放掉了。 
     //*p理论上是错误的，只是语法无错，编译不报错。                             
    system ("pause");
    return 0;
} 
/*malloc（）函数用法：（数据类型 *） malloc（A） A是字节数，可以是变量，常量，和表达式. 
                意义：分配A个字节的动态储存空间，并返回第一个字节的地址 
另一个内存分配函数：calloc()
    用法： （数据类型 *） calloc（A，B）
        意义：建立A个B字节的储存单元，（一共分配A*B个字节的内存） 并返回第一个字节的地址 ,而且其中的数据全部清零，而malloc得是未赋值。
  例子：# include <stdio.h>
# include <malloc.h>

int main (void)
{
    int i,h;
    int * p;
    printf ("输入元素个数：");
    scanf ("%d",&h);
    p = (int *)calloc(h,sizeof(int));
    for(i=0;i<h;++i)
    {
        printf ("输入第%d个元素：",i+1);
        scanf ("%d",&p[i]);
    }
    for(i=0;i<h;++i)
       printf ("%d  ",p[i]);
    
    system("pause");
    return 0;
} 
*/
