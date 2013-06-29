// 对象的定义与使用.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
using namespace std ;

class Cat //定义类 Cat
{
	int age;
	char color[10], Name[10]; //int 和 char 定义的三个变量为私有成员，
										//一般只能在类中访问，外部不可直接访问
public: //公共成员，可直接访问
	void name (void);
	void Age (int a)
	{
		age = a; //类中函数访问类中成员，直接访问
		return ;
	}
	void Its (void)
	{
		cout << "The Cat is " << Name <<endl
			<< "Color is " << color <<endl
			<< "Age is " << age << endl;  //类中函数访问类中成员，直接访问

		return ;
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	class Cat a; //定义对象
	a.Age (3); //类外成员访问 对象名.成员名
	a.name ();
	a.Its ();

	system ("pause");
	return 0;
}

void Cat :: name (void) // 定义类中函数 name
{
	cout << "输入名字：" ;
	cin >> Name ;
	cout << "颜色：" ;
	cin >> color ;

	return ;
}

/*	
	类的对象是该类的某一对象的实体，即该类类型的变量。
		声明定义形式： 类名 对象名；
	类中成员访问：直接访问成员名。
	类外访问成员：
		对象名.成员名 （只能访问public（公共的）属性下的成员。 ）
*/
