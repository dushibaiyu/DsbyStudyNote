/*两个以上函数，取相同的函数名，但是形参的个数或类型不同，
编译器根据实参和形参的类型及个数最佳匹配，自动确定调用哪个函数，这就是函数的重载*/

#include <iostream>
using namespace std;

int add (int, int);
int add (int, int, int);//对add()重载，形参个数不同 
double add (double, double);//对add()重载，形参类型不同
double add (double , int); //对add()重载，形参类型不同（有一个不同即为不同） 
double add (int, double); //对add()重载，形参类型不同（顺序与上个不同，亦可造成不同的重载） 
//注：函数重载只看形参和函数名，不看返回值。
//double add (int, int);为错，不允许出现两个或两个以上函数名和形参都相同的函数 

int main ()
{
	cout << add (10, 10) << endl;
	cout << add (10, 10, 10) << endl;//形参个数不同 
	cout << add (10.1, 10.0) << endl;//形参类型不同 
	cout << add (10.2, 10) << endl;//形参类型不同 
	cout << add (10, 10.3) << endl;//形参类型不同 
	
	return 0;
}
 
 int add (int a, int b, int c)
 {
 	return a+b+c;
 }
 
 int add (int a, int c)
 {
 	return a+c;
 }
 
 double add (double a, double c)
 {
 	return a+c;
 }
 
 double add (double a, int c)
 {
 	return a+c;
 }
 
 double add (int a, double c)
 {
 	return a+c;
 }
