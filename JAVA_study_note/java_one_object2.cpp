//一个类只生成一个对象，C++表示
/*C++中用指针实现会有不小心释放的问题。还有就是直接用静态成员变量实现。
这样的话，如果类成员太大的话，静态区域的内存需要的就大了···而且贯穿整个程序···
但是和不小心就导致程序崩溃来说，这个代价应该是相对较小的···
我感觉因该是用这个方法实现····
*/
#include <iostream>

using namespace std;

class A
{
	A(){}//把构造函数设置成私有的，外部就不可以访问，也就没发直接定义该类的对象
	static A aa;//声明一个静态成员
public:
	int i;
	static A * getA()
	{
		return &aa;
	}
};

A A::aa;//定义这个静态成员

int main ()
{
	//A * aa = new A();//错误，类的构造函数是私有的，类外不可访问
	//A aa;//错误，类的构造函数是私有的，类外不可访问
		A * aa = A::getA();//把在类中生成的对象的地址赋给aa
		A * bb = A::getA();//把在类中生成的对象的地址赋给bb,此时aa和bb相等
		
		if(aa == bb)
		{
			cout<< "aa = bb\n";
		}
		else 
		{
			cout<< "aa != bb\n";
		}
		
		aa->i = 100;
		cout <<"aa.i="<< aa->i<< "  "<<"bb.i="<<bb->i<<endl;
	
}