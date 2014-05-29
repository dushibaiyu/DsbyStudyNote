/*10.07.01
for和if的襄套使用 
求100以内可以整除3的说的和*/
# include <stdio.h> 
int main ()
{
	int i,sam=0;
	for (i=1;i<=100;++i)
	   {
   		if (i%3 == 0)
   		  sam += i;
   	   }
    printf ("%d\n",sam);
    system ("pause");
	return 0;
}
