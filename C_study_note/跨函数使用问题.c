/*跨函数使用问题*/
#include <stdio.h>
#include <malloc.h>
void f(int **); 
int main (void)
{
    int * p;
    f(&p);
    printf ("%d  \n",*p);
    
    system("pause");
    return 0;
}
void f(int ** q)
{
     *q = (int *)malloc(sizeof(int));
     **q =2;
     
}
/*
 
      
*/
