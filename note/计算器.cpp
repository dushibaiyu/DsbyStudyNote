#include<iostream> 
#include<cmath> 
#include<cstdlib> 
#include<cstring> 
#include<fstream>  
#include<ctime> 


#define EPS 1e-5       //定义精度常数
using namespace std;   //使用标准空间命名std
namespace NameCComplex //定义命名空间NameCComplex
{ 
	class CComplex         //定义一个CComplex类
	{ 
		private: 
		double Real,Image; 
		public: 
		CComplex(double real=0,double image=0) //构造函数
		{ 
			Real=real; 
			Image=image; 
		} 
	friend istream & operator>>(istream &is,CComplex &com); //重载输入
	friend ostream & operator<<(ostream &os,CComplex &com); //重载输出
	CComplex operator+(CComplex &com);                      //加法重载
	CComplex operator-(CComplex &com);                      //减法重载
	CComplex operator*(CComplex &com);                      //乘法重载
	CComplex operator+=(CComplex &com);                     //加法赋值重载
	CComplex operator-=(CComplex &com);                     //减法赋值重载
	CComplex operator*=(CComplex &com);                     //乘法赋值重载
	CComplex operator++();                                  //自加
	CComplex operator--();                                  //自减
	double mod(void);                                       //求复数的模
	int operator>(CComplex &com); 
	int operator<(CComplex &com); 
	int operator!=(CComplex &com); 
	int operator==(CComplex &com); 
	};                    
	struct User           //用户结构体类型定义          
	{ 
		char szName[20];      //用户名
		int nTime;            //使用次数
		int nTest;            //测试次数
		double alAve;        //平均成绩  
		int nAdd;            //加法次数
		int nSub;           //减法次数 
		int nMul;           //乘法次数 
		double dlScore[3];  //3次测试得分
	}user;					//定义全局变量

	CComplex CComplex::operator++()   //重载运算符"++"，实部与虚部均加1
	{ 
		Real++; 
		Image++; 
		return *this; 
	} 
	CComplex CComplex::operator--() //重载运算符"--"，实部与虚部均减1
	{ 
		Real--; 
		Image--; 
		return *this; 
	} 
	double CComplex::mod()     //求复数的模的平方，返回实部^2+虚部^2
	{ 
		return Real*Real+Image*Image; 
	} 
	int CComplex::operator>(CComplex &com)  //重载运算符">"，比较模的大小
	{ 
		if(mod()>com.mod()) 
		return 1; 
		else 
		return 0; 
	} 
	int CComplex::operator<(CComplex &com) 
	{ 
		if(mod()<com.mod())     
		return 1;        //若大，则返回1
		else 
		return 0; 
	} 
	int CComplex::operator!=(CComplex &com)
		//重载运算符"！="，分别判断复数的实部和虚部 
	{ 
		if(*this==com) 
		return 0; 
		else  
		return 1; 
	} 
	istream & operator>>(istream &is,CComplex &com) //重载输入，可以输入a+bi的形式
	{ 
		cout<<"请输入复数:"; 
		char s[80]; 
		is>>s;               //用字符串的形式接受复数
		int len=strlen(s);    //求出字符串的长度
		int n=0,sign=1; 
		//n为当前从字符串中提取出来的数字，初始化为0；sign是难道符号，初始化为正
		com.Image=com.Real=0; 
			for(int k=0;k<len;k++)   //判断接受的字符串是否合法
			{ 
				if((s[k]<'0' || s[k]> '9') && (s[k]!='+' && s[k]!='-' && s[k]!='i')) 
				{ 
					cout<<"error"<<endl;     
					return is;          //错误，输出出错信息并返回
				} 
			} 
		for(k=0;k<len;)     //顺序识别字符串中各字符
		{ 
			if(n!=0 &&(s[k]=='-'||s[k]=='+'))    //当前字符是否是符号位
			{ 
				com.Real=sign*n; 
				//是符号位，且n!=0，即n已被赋值，表明当前读取的是虚部的符号
				n=0;     //将原n*sign值赋给实部，将n清零，准备接受虚部的值
			} 
			if(s[k]=='-')    //当前字符为负号
			{ 
				sign=-1;k++;      //给符号标志赋值
			} 
			if(s[k]=='+')    //当前字符为正号
			{ 
				sign=1;k++;      //给符号标志赋值
			} 
			if(s[k]=='i')    //当前字符为'I'
			{ 
				if(k!=len-1)     //判断字符'I'是否为字符串中作后一个字符
				cout<<"error\n"; //如果不是，说明复数数据格式错误
				else 
				com.Image=sign*n;
				//是最后一个字符，复数对象已接受完，用sign*n为虚部赋值 
			break; 
			} 
			while(s[k]>='0' && s[k]<='9') 
				//当前字符在0～9之间，将数字字符转换成数字数值
			{ 
				n=n*10+s[k]-'0'; 
				k++; 
			} 
		} 
		if(s[len-1]!='i' && n!=0)
		//如果最后一个字符不是'I'，表示复数对象内只有实部，没有虚部 
		{ 
			com.Real=n*sign; 
		} 
		return is; 
	} 
	ostream & operator<<(ostream &os,CComplex &com)  //重载输入 
	{ 
		if(fabs(com.Image)<EPS)   // 如果虚部为0
		os<<com.Real;       //只输出实部
		else if((fabs(com.Real)<EPS))   //如果实部为0
		os<<com.Image<<"i";    //只输出虚部
		else if(com.Image>0) 
		os<<com.Real<<"+"<<com.Image<<"i"; 
		else 
		os<<com.Real<<com.Image<<"i";    //虚部为正
		return os; 
	} 
	CComplex CComplex::operator+(CComplex &com)   //加法重载
	{ 
		CComplex sum; 
		sum.Real=Real+com.Real;    //实部相加
		sum.Image=Image+com.Image;  //虚部相加
		return sum; 
	} 
	CComplex CComplex::operator*(CComplex &com)   //乘法重载
	{ 
		CComplex multi; 
		multi.Real=Real*com.Real-Image*com.Image; //乘积实部
		multi.Image=Real*com.Image+Image*com.Real; //乘积虚部
		return multi; 
	} 
	CComplex CComplex::operator-(CComplex &com)  //减法重载 
	{ 
		CComplex sub; 
		sub.Real=Real-com.Real; 
		sub.Image=Image-com.Image; 
		return sub; 
	} 
	CComplex CComplex::operator+=(CComplex &com) //重载加法赋值
	{ 
		Real=Real+com.Real; 
		Image=Image+com.Image; 
		return *this; 
	} 
	CComplex CComplex::operator-=(CComplex &com)  //重载减法赋值
	{ 
	Real=Real-com.Real; 
	Image=Image-com.Image; 
	return *this; 
	} 
	CComplex CComplex::operator*=(CComplex &com) //重载乘法赋值
	{ 
		double nReal=Real*com.Real-Image*com.Image; 
		double nImage=Real*com.Image+Image*com.Real; 
		Real=nReal; 
		Image=nImage; 
		return *this; 
	} 
	int CComplex::operator==(CComplex &com) //重载等于
	{ 
		if(Real==com.Real && Image==com.Image) 
		return 1; 
		else 
		return 0; 
	} 
	void Test(void)            //测试函数
	{ 
		user.nTest++; 
		cout<<"共10道题，做100以内的加减运算，满分100分:\n"; 
		double real1,real2,image1,image2,real3,real4,image3,image4; 
		CComplex answer,temp; 
		int score=0; 
		char op; 
		for(int i=0;i<=9;i++) 
			{ 
				/////为复数产生随机值
				real1=rand()%200-100; 
				image1=rand()%200-100; 
				real2=rand()%200-100; 
				image2=rand()%200-100; 
				CComplex a(real1,image1),b(real2,image2); 
				real3=rand()%20-10; 
				image3=rand()%20-10; 
				real4=rand()%20-10; 
				image4=rand()%20-10; 
				CComplex c(real3,image3),d(real4,image4); 
				op=rand()%3;      //产生随机加减乘法运算的三个值
				switch(op) 
					{ 
						case 0: 
						answer=a+b; 
						cout<<a<<"加上"<<b<<"等于"; 
						break; 
				case 1: 
						answer=a-b; 
						cout<<a<<"减去"<<b<<"等于"; 
						break; 
				case 2: 
						answer=c*d; 
						cout<<c<<"乘以"<<d<<"等于"; 
						break; 
					} 
			cin>>temp;      //输入用户计算值
			if(answer==temp) //比较用户计算值
			{ 
				score+=10; 
			} 
			else 
			{ 
				cout<<"此题做错了\n"; 
				cout<<"正确答案为:"<<answer<<endl; 
			} 
		} 
cout<<"你的最后得分是:"<<score<<endl; 
if(user.nTest<=3) 
{ 
user.alAve=0; 
user.dlScore[user.nTest-1]=score; 
for(int i=0;i<user.nTest;i++) 
user.alAve+=user.dlScore[i]; 
user.alAve=user.alAve/user.nTest; 
} 
else 
{ 
user.dlScore[0]=user.dlScore[1]; 
user.dlScore[1]=user.dlScore[2]; 
user.dlScore[2]=score; 
for(i=0,user.alAve=0;i<3;i++) 
user.alAve+=user.dlScore[i]; 
user.alAve=user.alAve/3; 
} 
cout<<"请按任意键继续\n"; 
cout.flush(); 
cin.get(); 
cin.get(); 
} 
void Add()             //复数加法运算函数
{ 
user.nAdd++; 
CComplex num1,num2,sum,Zero(0,0); 
cout<<"加法计算\n"<<"最少输入两个复数,并且以0结束\n"; 
cout<<"第一个复数:"; 
cin>>num1; 
cout<<"第二个复数:"; 
cin>>num2; 
sum=num1+num2; 
cout<<"第三个复数:"; 
cin>>num1; 
int i=4; 
while(!(num1==Zero)) 
{ 
sum=sum+num1; 
cout<<"第"<<i<<"个复数:"; 
cin>>num1; 
i++; 
} 
cout<<"加法结果是:"<<sum<<endl; 
cout<<"请按任意键继续\n"; 
cout.flush(); 
cin.get(); 
cin.get(); 
} 
void Sub()         //复数减法预算函数
{ 
user.nSub++; 
CComplex num1,num2,sub,Zero(0,0); 
cout<<"最少输入两个复数，并且以0结束\n"; 
cout<<"第1个复数:"; 
cin>>num1; 
cout<<"第2个复数:"; 
cin>>num2; 
sub=num1-num2; 
cout<<"第3个复数:"; 
cin>>num1; 
int i=4; 
while(!(num1==Zero))  
{ 
sub=sub-num1; 
cout<<"第"<<i<<"个复数:"; 
cin>>num1;
 i++;
} 
cout<<"减法结果是:"<<sub<<endl; 
cout<<"请按任意键继续\n"; 
cout.flush(); 
cin.get(); 
cin.get();
} 
void Mul()         //复数乘积函数
{ 
user.nMul++; 
CComplex num1,num2,mul,Zero(0,0); 
cout<<"乘法计算\n"<<"最少输入两个复数,并且以零结束\n"; 
cout<<"第一个复数:"; 
cin>>num1; 
cout<<"第二个复数:"; 
cin>>num2; 
mul=num1*num2; 
cout<<"第三个复数:"; 
cin>>num1; 
int i=4; 
while(!(num1==Zero)) 
{ 
mul*=num1; 
cout<<"第"<<i<<"个复数:"; 
cin>>num1; 
i++; 
} 
cout<<"乘法结果是:"<<mul<<endl; 
cout<<"请按任意键继续\n"; 
cout.flush(); 
cin.get(); 
cin.get(); 
} 
void Add1() 
{ 
user.nAdd ++; 
CComplex num1; 
cin>>num1; 
++num1; 
cout<<"自加的结果为"<<num1<<endl; 
cout<<"按任意键结束\n"; 
cout.flush(); 
cin.get(); 
cin.get(); 
} 
void Sub1()               //复数自加运算函数
{ 
user.nSub++; 
CComplex num1; 
cin>>num1; 
--num1; 
cout<<"自减的结果为"<<num1<<endl; 
cout<<"按任意键结束\n"; 
cout.flush(); 
cin.get(); 
cin.get(); 
} 
void compare()                //两复数比较函数
{ 
CComplex num1,num2; 
cout<<"输入两个复数\n"; 
cout<<"第一个复数:"; 
cin>>num1; 
cout<<"输入第二个复数\n"; 
cin>>num2; 
if(num1==num2) 
cout<<"这两个复数相等\n"; 
else if(num1>num2) 
cout<<num1<<"的模大于"<<num2<<"的模\n"; 
else if(num1<num2) 
cout<<num2<<"的模大于"<<num1<<"的模\n"; 
else 
cout<<"这两个复数的模相等\n"; 
cout<<"按任意键继续\n"; 
cin.get(); 
cin.get(); 
} 
void userprint()         //输出用户信息函数
{ 
cout<<user.szName<<"使用的次数为:"<<user.nTime<<endl; 
cout<<"其中:\t加法的次数:"<<user.nAdd<<"\t减法的次数:"<<user.nSub<<"\t乘法的次数:"<<user.nMul<<endl; 
cout<<"\t测试次数:"<<user.nTest<<"\t平均成绩:"<<user.alAve<<endl; 
} 
void Login()           //当前用户信息函数
{ 
char szName[20]; 
cout<<"欢迎试用本复数计算器!"<<endl;
cout<<"请输入您的姓名:"; 
cin.getline(szName,20); 
ifstream infile; 
User user1; 
infile.open("user.dat",ios::binary|ios::in); 
if(!infile)       
{ 
cout<<"没有原始记录文件，您是第一个用户!\n";   
strcpy(user.szName,szName);  
user.nTest++; 
return; 
} 
infile.read((char *)&user1,sizeof(User)); 
while(!infile.eof()) 
{ 
if(strcmp(user1.szName,szName)==0) 
{ 
user=user1; 
user.nTime++; 
cout<<"欢迎您再次使用复数计算器!"; 
userprint(); 
cin.get(); 
infile.close(); 
return; 
} 
infile.read((char *) &user1,sizeof(User)); 
} 
cout<<"欢迎您再次使用复数计算器!"; 
strcpy(user.szName,szName); 
user.nTime++; 
infile.close(); 
return; 
} 
void SaveFile()     //用户资料保存函数
{ 
userprint(); 
fstream file; 
User user1; 
file.open("user.dat",ios::binary|ios::in|ios::out); 
if(!file) 
{ 
cout<<"文件打开错误，不能进行更新!\n"; 
return; 
} 
file.seekp(0,ios::beg); 
while(!file.eof()) 
{ 
file.read((char *)&user1,sizeof(User)); 
if(strcmp(user1.szName,user.szName)==0) 
{ 
file.seekp(-(sizeof(User)),ios::cur); 
file.write((char *)&user,sizeof(User)); 
file.close(); 
return; 
} 
} 
file.close(); 
fstream outfile; 
outfile.open("user.dat",ios::binary|ios::app); 
outfile.write((char *)&user,sizeof(User)); 
outfile.close(); 
return; 
} 
} 
using namespace NameCComplex; 
int main(void)                   //主函数开始
{ 
srand(time(NULL));        //初始化随机数“种子”语句
Login();                  //当前用户信息函数
char strChoise[20];       //定义字符串名
do 
{ 
system("cls"); 
cout<<"\t这是一个简单的复数计算器程序，可以实现以下功能，请按对应的按键(1-7)\n\n\n"; 
//cout<<"\t  this program is writen by Ahsun(Test 0712 陈太阳)\n";
//cout<<"\t  E=mail:ahsunwork@hotmail.com  QQ:409861021  \n";
cout<<"\t=========================MENU===========================\n"; 
cout<<"\t1:多复数加法，以0结束\n"; 
cout<<"\t2:多复数减法，以0结束\n";         
cout<<"\t3:测试100以内的复数加减乘法运算，1次测试10道题\n"; 
cout<<"\t4:多复数乘法，以0结束\n"; 
cout<<"\t5:复数自加\n:"; 
cout<<"\t6:复数自减\n:"; 
cout<<"\t7:复数比较\n:"; 
cout<<"\t0:退出程序\n\n:"; 
cout<<"\t请您选择:"; 
cin>>strChoise; 
if(strcmp(strChoise,"1")==0)     //用户选1则调用Add()函数
Add(); 
else if(strcmp(strChoise,"2")==0)  //用户选2则调用Sub()函数 
Sub();                              
else if(strcmp(strChoise,"3")==0)   //用户选3则调用Test()函数
Test(); 
else if(strcmp(strChoise,"4")==0)   //用户选4则调用Add()函数
Mul(); 
else if(strcmp(strChoise,"5")==0)    //用户选5调用Add1()函数
Add1(); 
else if(strcmp(strChoise,"6")==0)    //用户选6则调用Sub1()函数
Sub1(); 
else if(strcmp(strChoise,"7")==0)     //用户选7则调用Compare()函数
compare(); 
else if(strcmp(strChoise,"0")==0)     //用户选0则结束调用函数
{ 
cout<<"\n\n\t欢迎下次继续使用复数计算器!\n\n"; 
break; 
} 
else 
{ 
cout<<"\n\t输入错误，请按任意键继续!\n"; 
cin.get(); 
cin.get(); 
} 
} 
while((strcmp(strChoise,"0")));       
SaveFile();                     //调用用户资料保存函数
return 0; 
}