// 构造函数.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>

using namespace std ;

class Cat 
{
	char color[10];
	char Name[10];
	int age;

public :
	Cat (){};//构造函数
	Cat (char a[], char b[], int c = 3);//构造函数，允许重载，可以带默认参数
	Cat (Cat &p)//拷贝构造函数
	{
		strcpy_s (color, p.color);
		strcpy_s (Name, p.Name);
		age = p.age;
		cout << "调用拷贝构造函数\n" ;
	}
	~Cat()//析构函数
	{
		cout << "对象释放\n" ;
	}
	void Its (void);
	void name (void);
	void Age (int a)
	{
		age = a; 
		return ;
	}
} ;

void ceshi ()
{
	Cat cb("wrihe","ceshi",10) ;
	cb.Its();
	return ;
}

int _tmain(int argc, _TCHAR* argv[])
{
	Cat cc("tree","yahoo") ;//可以带默认参数，构造函数
	cc.Its();

	Cat * cat = new Cat ;
	cat->name();
	cat->Age(5);
	cat->Its();

	delete cat;//释放对象时，调用析构函数

	if (1)
	{
		Cat ccb("dark","yahoo!",7) ;
		ccb.Its();
	}//ccb只在此作用域，执行完if语句，自动调用析构函数

	ceshi();//调用完函数，同样执行析构函数，释放该函数中对象的空间。

	Cat ac(cc) ;//调用拷贝构造函数，用一个对象去初始化另一个对象。即使用户不定义拷贝构造函数，也可以调用。
	ac.Its();

	system ("pause");
	return 0;
}//理论上，当主函数执行完毕，cc对象在释放时也会调用析构函数，只是程序执行结束了，没法看到输出结果。

void Cat::Its (void)
{
		cout << "The Cat is " << Name <<endl
			<< "Color is " << color <<endl
			<< "Age is " << age << endl;  //类中函数访问类中成员，直接访问

		return ;
	}

void Cat :: name (void)
{
	cout << "输入名字：" ;
	cin >> Name ;
	cout << "颜色：" ;
	cin >> color ;

	return ;
}
Cat::Cat (char a[], char b[], int c )
{
	strcpy_s (color, a);
	strcpy_s (Name, b);
	age = c;
}
/*构造函数：
	定义类时不可给每个成员变量赋初值，构造函数就是让在定义对象时给成员变量赋初值。
定义：
	构造函数是在类中定义的一种特殊的函数，它的函数名与类名相同。
	构造函数的主要功能是为对象分配空间，也可以用来为类成员变量赋初值，所以构造函数不能有返回值，甚至不能有return语句。

	一般格式：
声明：			函数名（也就是类名） （形参）；
定义：			 类名::函数名 (形参) {};

	性质：
		构造函数的名字必须和类名相同；
		构造函数的参数可以是任何数据类型，但它没有返回值，不能为它定义返回类型，包括void在内；
		对象定义时，编译系统会自动地调用构造函数完成对象内存空间的分配和初始化工作；
		构造函数是类成员函数，具有一般成员函数的所有性质，可以访问类的所有成员，可以是内联函数，可以带有参数表，可以带有默认
		的形参值，还可以重载。


	拷贝构造函数：
		拷贝构造函数就是同类的对象克隆。
		如果用户没有声明类的拷贝构造函数，系统会自动生成一个缺省的拷贝构造函数。(所以即使用户不自定义，也可以调用，去实现基本的对象克隆。)
		拷贝构造函数性质和一般构造函数相同，只是其形参必须是本类对象的引用。
		一般格式：
声明：			函数名（也就是类名） （类名 &对象名）
定义：			 类名::函数名 (类名 &对象名) {};
		调用拷贝构造函数一般的三种情况：
			1.用类的对象去初始化类的另一个变量。
			2.如果函数的形参是类的对象，调用该函数进行形参和实参结合的时候。
			3.函数的返回值对对象赋值。


析构函数：
	当对象消亡时（出作用域）所做的工作（执行）。用于对象被释放时进行清理工作。析构函数是在对象生存周期即将结束的时刻由系统自动调用，
	对象消失，对象所占的内存空间也将释放。

	特点：
		析构函数与类名相同，在其前加上“～”;析构函数也是公有属性，没有返回值，也不接受任何参数，但可以是虚函数。

声明：		～函数名（也就是类名） （）
定义：		 类名::函数名 () {};
	*/