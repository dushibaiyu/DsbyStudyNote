#include <stdio.h>
int main (void)
{
	int i,sum = 0,cnt = 0;
	float avg = 0;
	for (i=1; i<=100; ++i)
	{
		if (i%2 != 0)
        {
        	++cnt;
			sum+=i;
        }
	}
	avg = 1.0*sum/cnt;
	printf ("一共有%d个奇数\n所有的和是%d\n平均数是%f\n",cnt,sum,avg) ;
	//system("pause");
	return 0;
}
