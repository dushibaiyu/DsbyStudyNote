# include <stdio.h>
int main (void)
{
	int i;
	float sam = 0;

	for (i=1; i<=100; ++i)
    {
		sam = sam+1.0/i; //是OK的 推荐使用
			//sum = sum + (float)(1/i); 这样写是不对的 
			//也可以这样写:  sum = sum + 1 / (float)(i);   不推荐
		/*强制类型转换:
		   格式：（ 数据类型）（表达式）
		   功能：把表达式的值强制转化为前面所执行的数据类型。*/ 
 	}  
    printf ("sam = %f", sam);//float必须用%f输出
    system ("pause"); 
	return 0;
}
