# include <stdio.h>

void hnt (int a,char x, char y, char z)
{
	if (1 == a)
	{
		printf ("把第%d个盘子从%c移到%c\n",a,x,z);	
	}
	else 
	{
		hnt (a-1,x,z,y);
		printf ("把第%d个盘子从%c移到%c\n",a,x,z);
		hnt (a-1,y,x,z);
	}
} 

int main (void)
{
	hnt (2,'A','B','C');
	
	return 0;
}
/*
汉诺塔的伪算法 ：
 1.借助C把n-1个盘子从A移动到B； 
 2.直接把n从A移动到C；
 3.借助A把n-1个盘子从B移动到C。 
*/
