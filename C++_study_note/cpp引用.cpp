/*
C++中，引用只是一个别名，只能在定义时初始化（类似一个常量类型）。
常在函数传递中使用，在哪儿定义在哪儿用，尽量不要在主函数中使用

*/

#include <iostream>

using namespace std;


int main ()
{
	int a = 5;
	int & r = a;//定义一个引用，并初始化
	cout << &a << "   " << &r <<endl;//输出地址相等···，仅仅是一另一个名字而已。

	return 0;
}