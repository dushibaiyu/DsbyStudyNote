/*10.06.23
if..else..的用法：*/

#include<stdio.h> 
#include<conio.h>

int main (void)
{
	int i,j;
	printf ("输入两个整数，中间用一个空格隔开\n");
	scanf ("%d %d",&i,&j);
	if (i > j) 
	  printf ("%d大于%d\n",i,j);
    else 
	  printf ("%d小于%d\n",i,j);//if与else是一整体，写程序时，为了区分范围与易读，往往与下一个语句中间隔一空语句。 
    char ch;
    while ((ch = getchar()) != '\n')
      continue;
    getchar ();  
    printf ("程序结束\n"); 
    system("pause");
	return 0;
}
/*if(表达式)
     语句1；
  else
     语句2；
意义：如果if后表达式的值为真，执行语句1，
否则，也就是表达式值为假，执行语句2。
else后的范围与if相同。*/
