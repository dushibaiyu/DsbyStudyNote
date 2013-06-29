#include <iostream>
using namespace std;

int add (int ,int =10, int =5);//全局预定义参数值
void ff (void);

int main ()
{
	cout << add (1) <<endl;//输出16，用的全局预定义形参
	ff ();

	return 0;
}

int add (int a, int b, int c )
{
	return a+b+c;
}

void ff (void)
{
	int add (int ,int =1, int =1);//在ff()函数中的预定义参数值
	cout << add (1) <<endl;//输出 3，用在这个函数内里的默认形参
}
/*在相同的作用域内，默认形参值的值应保持唯一，
但如果在不同的作用域内，允许说明不同的默认形参*/
