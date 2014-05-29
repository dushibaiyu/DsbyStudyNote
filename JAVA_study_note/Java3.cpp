//与C++过程和对象对比，C++面向对象表示
//三角形的周长与面积

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
	Sjx(){}//构造函数，重载
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
	cout << s.zhouchang()<<"  "<<s.mianji()<<endl;
	
	Sjx * s1 = new Sjx();//声明并定义指向Sjx类的指针s1
						//并在堆中动态分配一块Sjx大小的内存，使指针s1指向这块内存
	s1->chushihua (4,5,6);//初始化对象成员
	cout << s1->zhouchang()<<"  "<<s1->mianji()<<endl;
	
	return 0;
}

double Sjx::mianji ()//定义求面积的函数
{
	double p = (a+b+c)/2.0;
	return sqrt(p * (p-a) * (p-b) * (p-c));//sqrt在头文件cmath中
}
