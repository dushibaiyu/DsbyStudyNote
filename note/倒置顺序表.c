#include <stdio.h>

void daozhi (int *, int);

int main ()
{
	int a[10] = {1,2,3,4,5,6,7,8,9,10};
	int i;
	for (i=0;i<10; ++i)
	{
		printf ("%d\t",a[i]);
	}
	printf ("\n");
	
	daozhi(a,10);
	for (i=0;i<10; ++i)
	{
		printf ("%d\t",a[i]);
	}
	printf ("\n");
	
	return 0;
} 

void daozhi (int * p,int a)
{
	int i,j;
	for (j=0,i=a-1;j<i;++j,--i)
	{
		int t = p[i];
		p[i] = p[j];
		p[j] = t; 
	}
	
	return ;
}

