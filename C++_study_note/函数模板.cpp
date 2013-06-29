/*函数模板可以用来创建一个通用功能的函数，以支持多种不同形参，进一步简化重载函数的函数体设计。
*/ 
#include <iostream>

using namespace std;

template <typename T>
T abs (T x, T y)//函数模板 
{
	return x<y?x:y;
}
 
int main ()
{
	int a = 10,c=13;
	double b = 10.67,d = 12.9;
	cout << abs(a,c) <<endl; //abs(a)为模板函数 
	cout << abs(b,d) <<endl;
	
	return 0;
}
/*声明方法：template <typename 标识符>
用一个标识符代替数据类型，再需要类型定义时用标识符代替数据类型，根据实参类型推导出函数模板的类型参数，
在实例化生成模板函数调用。 
 注：template < >尖括号里可以定义多个标识符。
 	每个模板函数前都要有标识符声明，不能声明一次而构造多个模板函数。
 	模板函数不能声明与定义分开（也就是：主函数前声明，主函数后定义），必须在声明时定义。
 	多个模板函数的标识符可以定义相同，也就是一个标识符可以多次定义使用。
例：
#include <iostream>
#include <stdlib.h>

using namespace std;
template <typename T, typename T2>
T yy (T a, T2 b)
{
	return  0;
}

template <typename T2, typename T>
T2 zz (T2 c, T y)
{
	return 0 ;
}

int main ()
{
	cout <<"gjhgj\n";
	int i = yy (3 ,3.67);
	int z = zz (3 , 7.89);

	system ("pause");
	return 0;
}

//T yy (T a , T2 b)
//{
//	return;			此分开写为错误。
//}
*/

