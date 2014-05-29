/*10.06.23
if..else...if..else..的用法：*/
#include <stdio.h>
int main(void)
{
	int a,s;
	printf ("输一个整数\n");
	scanf ("%d",&a);
	printf ("再输一个整数\n");
	scanf ("%d",&s);
	if (a>s) 
	   printf ("%d大于%d\n",a,s);
    else if (a=s)
       printf ("%d等于%d\n",a,s);
    else 
	   printf ("%d小于%d",a,s);
       
    system ("pause");
	return 0;
}
/*if (A)
    语句1； 
  else if (B)
     语句2； 
  else if (C)
      语句3； 
  ``````
  else
    语句n；
功能：如果A成立执行“语句1”，否则看B是否成立,成立就执行“语句2”，
若不成立就看C，以此类推，若都不成立执行“语句n”。 
  
*/ 
