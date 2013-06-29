/*比较3个数大小：10.06.24*/
#include<stdio.h>
int main (viod)
{
	int a,b,c,t;
	printf ("输入三个数,中间用空格隔开\n") ;
	scanf ("%d %d %d",&a,&b,&c); 
	if (a<b) 
	{
		t = a;
		a = b; 
		b = t; 
	}
	if (a<c)
	{
		t = a;
		a = c;
		c = t;
	}
	if (b<c)
	{
		t = b;
		b = c;
		c = t;
	}
/*	if (a>b&&a>c) 
	{
		t = a;
		if (b>c)
		  a =t;
		else 
	   {
  		  a =b;
  		  b =c;
  		  c = a;
  		  a = t;
  		}
	}
    else if(b>a&&b>c)
    {
    	t = b;
    	if (a>c)
    	{
	    	b = a;
	    	a = t;
	    }
	    else 
	    {
    		b=c;
    		c=a;
    		a=t;
    	}
    }
    else 
    {
    	t = c;
    	if (a>b)
    	{
	      c = b;
		  b =a;
		  a = t;	
	    }
	    else 
	    {
    		c = a;
    		a = t;
    	}
    }我自己写的*/
	
	printf ("%d>%d>%d",a,b,c) ;
	system ("pause");
	return 0;
} 
