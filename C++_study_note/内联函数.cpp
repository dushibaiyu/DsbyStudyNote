/*内联函数：
	为了克服函数不断压栈出栈降低运行速度。 
	作用：既有函数的模块化方便，又有直接代码的运行速度。
	内联函数就相当于把代码直接写在被调用中。 
*/
#include <iostream> 
using namespace std;

inline int ff (int);//声明时加上inline关键字

int main (void)
{
	int h = 6;
	h = ff(h);
	printf ("%d\n",h);
	
	return 0;
}

int ff (int a)//定义时inline关键字可有可无···
{
	int p = a;
	p++;
	if (p == a) 
		p *= 6;
	return p;
}
/*注意：
	内联函数中不能出现循环语句（for，while，do··while）和开关语句（switch）
	在调用内联函数前要先声明
	 内联函数不能有异常接口声明 
*/
