/*
	10.7.3
	本程序不对， 因为循环中更新的变量不能定义成浮点型；
	因为float合double都不能保证可以精确的存储一个小数，有些只是一个近似值。 
*/

# include <stdio.h>

int main(void)
{
	float i;
	float sum = 0;  

	for (i=1.0; i<=100; ++i)
	{
		sum = sum + 1/i;
	}
	printf("sum = %f\n", sum);  

    system ("pause");
	return 0;
}
/*举例：
    有一个浮点型变量x，如何判断x的值是否为零：
	if （0 == x）是；
	 else 不是； （不对） 
	 if （|x-0.000001| <0.000001）是零；
	 else 不是；（对）
	  
*/ 
