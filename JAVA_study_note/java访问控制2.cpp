#include <iostream>
#include <string>

using namespace std;

class cat
{
private :
	string name,color;
	unsigned int age;
protected:
	string from;
public:
	cat(string a, string b, unsigned int i, string c)
	{
		name = a ; color = b ; age = i ; from = c;
	}
	cat(){}
	void initialize (string a, string b, unsigned int i, string c)//初始化
	{
		name = a ; color = b ; age = i ; from = c;
		return ;
	}
	void print ()//打印 输出
	{
		cout << "Name is :" << name << "\nColor is :" <<color << "\nAge is :" <<age <<"\n From for :"<<from<<endl;
		return ;
	}
	~cat()
	{
		cout <<"This object 已经销毁。"<<endl;
	}
};

int main()
{
	cat i("name", "red", 2, "china");//静态栈中分配对象，并利用初始化函数给对象初始化
	
	// cout << i.name << i.age<<endl;//错误，无法访问private成员
	//cout << i.from <<endl;//同样错误，无法访问protected成员
	
	i.print();//可以访问public成员。

	return 0;
}