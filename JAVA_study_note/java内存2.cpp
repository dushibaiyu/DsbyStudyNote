//Java的堆与栈的内存分配 C++对比
//例子还取三角形

#include <iostream>
#include <cmath>

using namespace std;

class Sjx
{
	int a,b,c; //私有成员；C++中class类型默认的是私有的
public:			//以下是公有成员
	Sjx(int e,int d, int h)// 构造函数
	{
		a=e, b=d, c=h;
	}
	Sjx(){}
	void chushihua(int e,int d, int h)//初始化成员变量函数
	{
		a=e, b=d, c=h;	
	}
	int zhouchang()//生命和定义求周长函数
	{
		return a+b+c;
	}
	double mianji ();//声明求面积函数
};

int main()
{
	Sjx s(4,5,6);//声明并定义对象S，并用构造函数初始化成员变量。
				//静态在栈中分配
	cout << s.zhouchang()<<" S "<<s.mianji()<<endl;
	
	Sjx * s1 = new Sjx(3,4,5);//声明并定义指向Sjx类的指针s1
						//并在堆中动态分配一块Sjx大小的内存，使指针s1指向这块内存
						//在自动调用构造函数初始化成员变量
	cout << s1->zhouchang()<<" S1 "<<s1->mianji()<<endl;//C++中动态在堆中分配的内存用指针类来访问
													//在用指针访问时格式是 指针->成员   在栈中分配的是 指针.成员
										//Java不支持在栈中分配类，所以Java访问类成员都是 引用名.成员
										
	Sjx * s2 = new Sjx;//自动调用Sjx()构造函数。书写成new Sjx()亦可
						//在Java中这样书写错误。
	s2->chushihua(5,6,7);//调用初始化函数，初始化对象成员
	cout << s2->zhouchang()<<"  S2 "<<s2->mianji()<<endl;
										
	int a[5]; //静态在栈中分配数组
	a[1] = 10;
	cout <<a[1]<<endl;
	
	int * i = new int[5]; //动态在堆中分配数组
	i[1] = 20;
	cout << i[1] <<endl;
	
	int j = 5;//静态在栈中分配变量j，并赋值为5
	int * h = new int(3);//在堆中动态分配空间，并把地址赋给静态在栈中分配的指针h，并把这块内存赋值为3
	cout << j <<endl<< *h <<endl;
	
	//C++不支持自动回收内存，在栈中分配的内存都有其作用域，在堆中分配的需要我们手动去清除我们不需要的内存空间。否则就会内存溢出
	delete s1;//删除S1所指向的内存空间，也就是删除s1所指向的呢个类的存储空间
	delete []i;//删除i数组，也就是i所指向的连续空间。当指针指向的是一个数组时，必须加上[]
	
	return 0;
}

double Sjx::mianji ()//定义求面积的函数
{
	double p = (a+b+c)/2.0;
	return sqrt(p * (p-a) * (p-b) * (p-c));//sqrt在头文件cmath中
}


/*
	在C++中，任何类型都可以在栈中和堆中都可以分配内存。堆中的内存都是用指向这个类型的指针控制。
*/