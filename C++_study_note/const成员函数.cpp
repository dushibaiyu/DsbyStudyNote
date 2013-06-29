//const成员函数，作用是在函数不能修改类的变量成员

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
	void Its (void) const //const成员函数，作用是在函数不能修改类的变量成员
	{
		cout << "The Cat is " << Name <<endl
			<< "Color is " << color <<endl
			<< "Age is " << age << endl;  //类中函数访问类中成员，直接访问
		//Age = 5;//错误，因为要修改成员变量
		return ;
	}
	void its(void) const;//const成员函数声明，声明时要加上const
};

int main()
{
	class Cat a; //定义对象
	a.Age (3); //类外成员访问 对象名.成员名
	a.name ();
	a.Its ();
	a.its();

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

void Cat::its(void) const//const函数定义，定义时也要加上
{
	cout << "const成员函数" <<endl;
	//Age = 10;//错误，因为要修改成员变量
}


