/*结构体的使用:通过函数完成输入和输出*/
# include <stdio.h>
# include <conio.h>

struct yy 
{
       int b;
       float c;
};

void shuruy (struct yy *);
//void shuchuy (struct yy);
void shuchuy (struct yy *);

int main (void)
{
    struct yy h,y;
    shuruy (&h);
    shuchuy (&h);
    //shuchuy (h)
    y = h;//结构的相互赋值. 
    shuchuy (&y);
    
    system ("pause");
    return 0;
}
 
void shuruy (struct yy *p)//这个必须发送地址才能改变 
{
    char ch;
    
    printf ("输入学号：");
    scanf ("%d",&p->b);
    
    while ( (ch=getchar()) !='\n')
          continue;
          
    printf ("输入成绩："); 
    scanf ("%f",&p->c); 
    return ;
}

/*void shuchuy (struct yy hy)//输入接受数据也可以 
{
   printf ("%c  %d  %f\n",hy.a,hy.b,hy.c); 
   return ; 
}
*/

void shuchuy (struct yy *p)//但一般还是发送地址 
{
   printf ("结果是：%d  %f\n",p->b,p->c); 
   return ; 
}/*
发送地址的优点：1.快速的传输数据 2.耗用内存小 3.执行速度更快，
结构体变量不可进行加减乘除运算。可以相互赋值。 
*/
