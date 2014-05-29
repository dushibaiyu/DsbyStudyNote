//一个类只生成一个对象，C++表示
/*C++中完全用指针实现，不推荐使用，弊病太大···、

C++中的堆中的管理完全是可以控制的，这就导致了另一个问题，如果多个指针同时指向这块内存，如果用其中一个指针释放了这块内存，
其他指针在访问时，就会导致程序崩溃····
*/
#include <iostream>

using namespace std;

class A
{
	A(){}//把构造函数设置成私有的，外部就不可以访问，也就没发直接定义该类的对象
	static A * aa;//声明一个指向该类的指针
public:
	int i;
	static A * getA()
	{
		return aa;
	}
};

A * A::aa = new A;//定义和初始化aa，在堆中分配一个对象空间

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