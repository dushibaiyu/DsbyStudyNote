//与C++过程和对象对比，java表示
//三角形的周长与面积

class Sjx //定义三角形类
{
	int a;
	int b;
	int c;
	int zhouchang () //a b c变量和此函数同属一个类，故，不需要形参
	{       			//Java中函数也叫方法
		return a+b+c;
	}
	double mianji ()
	{
		double p=(a+b+c)/2.0;
		return Math.sqrt(p * (p-a) * (p-b) * (p-c));
		//Java没有头文件，利用库中方法用 库名.方法
	}
}
//java是完全面向对象语言，所有操作都要在类中进行。
class Java1  //这个名字要和文件名字一致，否则运行可能错误
{
	public static void main (String[] args) //入口，必须这么写
	{
		Sjx g = new Sjx();//声明和定义对象g，
		g.a=4;
		g.b=5;
		g.c = 6;
		System.out.printf ("%d  %f",g.zhouchang(), g.mianji());
	}
}
//在命令行中用javac编译时要输入文件名，运行时要输入java加类名
//一般把含有主方法的类和文件名命名一致