#include <iostream>

using namespace std;

int runyear (int);
int mom1 (int ,int);
int mom2 (int ,int);
int mom3 (int ,int);
int mom4 (int ,int);
int mom5 (int ,int);
int mom6 (int ,int);
int mom7 (int ,int);
int mom8 (int ,int);
int mom9 (int ,int);
int mom10 (int ,int);
int mom11 (int ,int);
int mom12 (int ,int);

int main(int argc, char *argv[])
{
	int year,mom,day;
	int sum;
	cout<<"请输入年月日（中间用空格隔开）：" ;
 	cin >>year>>mom>>day ;
 	switch (mom)
 	{
 		case 1:
 			sum=mom1(year,day);
 			break;
		case 2:
			sum=mom2(year,day);
			break;
		case 3:
			sum=mom3(year,day);
			break;
		case 4:
			sum=mom4(year,day);
			break;
		case 5:
			sum=mom5(year,day);
			break;
		case 6:
			sum=mom6(year,day);
			break;
		case 7:
			sum=mom7(year,day);
			break;
		case 8:
			sum=mom8(year,day);
			break;
		case 9:
			sum=mom9(year,day);
			break;
		case 10:
			sum=mom10(year,day);
			break;
		case 11:
			sum=mom11(year,day);
			break;
		case 12:
			sum=mom12(year,day);
			break;
		default:
			sum = -10;
	 }
	 if (sum < 0)
	 	cout << "您输入的日期不合法！\n" ;
 	else
	 	cout << "这天是" << year<<"年的第"<< sum << "天。\n" ;
	
	return 0;
}

int runyear (int year)
{
	if (0 == year % 100)
	{
		if (0 == year % 400)
			return 29;
		else 
			return 28;
	}
	else 
	{
		if (0 == year % 4)
			return 29;
		else
			return 28;
	}
}

int mom1 (int year,int day)
{
	if (day > 31)
		return -10;
	else 
		return  day;
}

int mom2 (int year,int day)
{
	if (day > runyear(year))
		return -10;
	else
		return 31+day;
}

int mom3 (int year,int day)
{
	if (day > 31)
		return -10;
	else 
		return  day+31+runyear(year);
}

int mom4 (int year,int day)
{
	if (day > 31)
		return -10;
	else 
		return  day+31+runyear(year)+31;
}

int mom5 (int year,int day)
{
	if (day > 31)
		return -10;
	else 
		return  day+31+runyear(year)+31+30;
}

int mom6 (int year,int day)
{
	if (day > 31)
		return -10;
	else 
		return  day+31+runyear(year)+31+30+31;
}

int mom7 (int year,int day)
{
	if (day > 31)
		return -10;
	else 
		return  day+31+runyear(year)+31+30+31+30;
}

int mom8 (int year,int day)
{
	if (day > 31)
		return -10;
	else 
		return  day+31+runyear(year)+31+30+31+30+31;
}

int mom9 (int year,int day)
{
	if (day > 31)
		return -10;
	else 
		return  day+31+runyear(year)+31+30+31+30+31+31;
}

int mom10 (int year,int day)
{
	if (day > 31)
		return -10;
	else 
		return  day+31+runyear(year)+31+30+31+30+31+31+30;
}

int mom11 (int year,int day)
{
	if (day > 31)
		return -10;
	else 
		return  day+31+runyear(year)+31+30+31+30+31+31+30+31;
}

int mom12 (int year,int day)
{
	if (day > 31)
		return -10;
	else 
		return  day+31+runyear(year)+31+30+31+30+31+31+30+31+30;
}
