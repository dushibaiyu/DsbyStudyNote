//堆中分配内存.cpp

#include <iostream>

using namespace std;

class A 
{
public:
	A(){cout<<"调用构造函数，创建对象\n";}
	~A(){cout<<"调用析构函数，释放对象\n";}
};

int main ()
{
	A * p = new A;
	
	delete p;//在没有这句话的时候，对堆中的对象并不被释放，导致内存泄漏
	return 0;
}