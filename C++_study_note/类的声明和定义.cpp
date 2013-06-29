// 类的声明和定义
//

//#include "stdafx.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

class Cat
{
	int age;
	char color[6], name[10]; //私有成员，紧跟类名后声明，关键字private省略
public :    //公共成员
	void Dcat (char *  nm, char * cc, int a)//在类中声明时定义函数
	{
		int i ;
		age = a; //类的成员函数可以直接使用类中定义的数据成员。
		for (i = 0 ; i<10 ; ++i)
		{
			name[i] = nm[i];
		}
		for (i=0 ; i<6 ; i++)
		{
			color[i] = cc[i];
		}

		return ;
	}
	void Kcat () ;
} ;

int main()
{

	system ("pause");
	return 0;
}

void Cat :: Kcat () //在函数外定义类中的函数
{
	cout << name << "\t" << age << "\t" << color <<endl; //类的成员函数可以直接使用类中定义的数据成员。

	return ;
}
/*
类： 类是具有相同属性和行为的一组对象的集合，它为属于该类的全部对象提供了统一的抽象描述，其内部包括属性和行为两部分。
	   函数是将逻辑上相关的语句和数据封装，用于完成特定的功能。
	   类则是逻辑上相关的函数与数据的封装，它是对待所要处理问题的描述。
	类是一种用户自定义类型，声明形式：
		class 类名称
		{
			public:
					公有成员（外部接口）；//任何外部函数都可以访问。
			private:    //如果紧跟类名称后面声明私有成员，关键字private可以省略。
					私有成员；  //只允许本类中的函数访问。
			protected:
					保护型成员；  //与private相似，类外不可访问，差别在继承和派生时对派生类的影响不同。
		} ；
		成员又分为 数据成员（属性/方法） 和 成员函数（行为）。
		类的成员函数定义：
		（1）在类中声明时定义，内联函数一般都在类中定义。
		（2）在类外定义：定义格式：
		类型说明符 所在类的类名 :: 函数名 (形参列表)
		{
			函数体；
		}

		注：类的成员函数可以直接使用类中定义的数据成员。
			成员函数允许重载函数和带默认参数的函数。
*/

