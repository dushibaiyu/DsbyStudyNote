//C++继承
/*
    公有继承：公有继承中，子类继承父类的成员，在子类中，父类的保护成员和公有成员属性保持不变，而父类的私有成员在子类中无法访问。
    私有继承：私有继承中，子类继承父类的成员，在子类中，父类的保护成员和公有成员属性在子类中都为私有成员，父类的私有成员子类无法访问。
    保护继承：私有继承中，子类继承父类的成员，在子类中，父类的保护成员和公有成员属性在子类中都为保护成员，父类的私有成员子类无法访问。
    C++中，继承的属性变化都是保护和公共的，私有成员在子类中永远无法访问。
	*/
#include <iostream>

using namespace std;

class Human //定义父类
{
	double height;
	double weight;
protected:
	int ege;
public:
	inline void sethg(double);
	inline void  setwg (double);
	inline double gethg(void);
	inline double getwg(void);
};

class Student : public Human //公有继承Human类
{
	double score;

public:
	void sets(double i){score = i; return ;}
	double gets(void){return score;}
	void print (void)
	{
		sethg(32.2);//子类可以访问父类的共有成员，相当于子类的共有成员，
			    //如果是保护继承，同样可以访问，相当于子类的保护成员
			    //如果是私有继承，同样可以访问。相当于子类的私有成员
		ege  = 10;//子类中能访问父类的保护成员，相当于子类的保护成员
			   //如果是保护继承，同样可以访问，相当于子类的保护成员
			    //如果是私有继承，同样可以访问。相当于子类的私有成员
	//	cout << height <<endl; 父类的私有子类中无法访问，无论什么继承方式
		cout << score <<endl;
	}
};

int main ()
{
	Student m;
	m.sethg (2.2);//子类外也能访问父类公有继承过来的
		      //如果是保护继承，则世错误的，类外不能访问保护成员
		      //如果是私有继承，同样错误，类外不能访问私有成员
	m.sets (93.5);
	m.print();
	cout <<m.gethg()<<endl;


	return 0;
}

void Human::sethg (double i)
{
	height = i;
	return ;
}

void Human::setwg(double i)
{
	weight = i;
	return ;
}

double Human::gethg(void){return height;}

double Human::getwg(void){return weight;}
