/*1.06.23
if的范围问题：*/ 
#include <stdio.h> 
int main ()
{
	if(4>5)
	  printf ("cuowu\n"); 
    printf ("zhengque\n");
    if (4>5)
    {
    	printf ("wode\n");
    	printf ("tade\n");
    }
    system ("pause");
	return 0;
}
/*if范围问题：
   if（表达式）
     语句1；
  语句2；
解释：if只能控制语句1的执行或不执行，语句2不受其控制，一定执行。
if（表达式）
{
	语句1；
	语句2； 
}
解释：此时语句1和语句2都受其控制。
由上而知：if默认只能控制一个语句的执行或不执行，
若要控制多个语句要把这些语句用大括号{}扩起来。*/
/*C语言对真假的判断：
非零是真
零就是假

真用1表示
假用零表示*/ 
