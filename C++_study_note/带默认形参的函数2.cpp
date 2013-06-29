
#include <iostream>
using namespace std;

int add (int ,int =10, int =5);//如果先声明再定义函数，要在声明时预定义参数值（同样可以不写变量名） 

int main ()
{
	cout << add (1) <<endl;
	cout << add (1,2) <<endl;
	cout << add (1,2,3) <<endl;
	
	return 0;
}

int add (int a, int b, int c )//在声明中预定义参数值 ,在此处（定义函数 ）不可预定义值 
{
	return a+b+c;
}
/*默认形参值必须是从右往左的顺序定义
例：int add (int b = 10,int c=5, int a); （错） 
int add (int  = 10,int a, int c=5); （错） 
int add (int a, int b = 10,int c=5); （对）*/
