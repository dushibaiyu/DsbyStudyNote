/*10.06.24
互换两个数字:把a的结果为大*/
#include<stdio.h>
int main (viod)
{
	int a,b ;
	printf ("输入一个整数\na=");
	scanf ("%d",&a);
	printf ("再输入一个数\nb=");
	scanf ("%d",&b) ;
    int t;  //定义临时变量
    /*  a = b;  （这时，a与b的值相等） 
    	b = a;  (这样错误，应为上个语句a与b值已相等a的原来值已丢失。）*/
    //下面是正确的方法： 
	t = a;
    a = b;
    b = t;
    printf ("a = %d\nb = %d",a,b);
    system ("pause");
 	return 0;
}
