//与C++过程和对象对比，C++面向过程表示，等同于C
//三角形的周长与面积

#include <iostream>
#include <cmath>//C中math

using namespace std;

int zhouchang (int a, int b, int c)
{
	return a+b+c;
}

double mianji (int a, int b, int c)
{
	double p = (a+b+c)/2.0;
	return sqrt(p * (p-a) * (p-b) * (p-c));//sqrt在头文件cmath中
}

int main ()
{
	int a=4, b= 5, c=6;
	cout << zhouchang(a,b,c)<<"  "<<mianji(a,b,c)<<endl;

	return 0;
}