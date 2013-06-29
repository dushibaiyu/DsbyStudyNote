/*函数定义时可以预先定义出默认形参值，调用时如果给出实参，则用实参值初始化形参，
如果没有给出实参，则用预先定义的形参值。*/
#include <iostream>
using namespace std;

int add (int x=5, int y = 6)//aad函数就是带有默认参数的函数 
{
	return x+y;
} 

int main ()
{
	cout << add() <<endl;//当调用函数不给函数传值时，就使用默认值 ,结果11 
	cout << add(10) <<endl;//只传一个值时，没传值的使用默认值 ，结果16 
	cout << add(10 , 12) <<endl;//都传的话 ，使用实参所传的值 ，结果22 
	
	return 0;
}
