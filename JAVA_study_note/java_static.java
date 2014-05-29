//类中static静态成员····
/*类中的static成员属于类本身，不属于任何对象····可以直接用：类名.成员名  访问
在内存分配中静态成员和代码区共用一块区域，不属于栈，也不属于堆
*/

class A
{
	public int i=1;
	public static int a=0;
	public static void t()//静态方法只能访问静态成员
	{
		System.out.printf("静态a=%d\n\n",a);
		//System.out.printf("%d\n",i);//错误，静态方法不能访问非静态成员
		//b();//错误，静态方法不能访问非静态成员
	}
	public void b()//非静态方法可以访问静态成员
	{
		System.out.printf("非静态a＝%d  ",a);
		System.out.printf("非静态i＝%d\n\n",i);
		t();//非静态成员可以访问静态成员
	}
}

class java_static 
{
	public static void main (String[] args)
	{
		A aa = new A();
		A bb = new A();
		aa.b();//a=0,i=1对象默认值
		bb.b();//a=0,i=1对象默认值
		System.out.printf("\n\n");
		
		aa.i = 10;
		aa.a = 20;
		aa.b();//a=20,i=10 aa中i已被赋值改变，
		bb.b();//a=20,i=1 a是静态成员，无论生成多少对象静态成员一直都只是一个，所以a属于类，所以那个对象访问结果都一样
		A.t();//a=20 静态对象可以直接用 类名.成员名 访问,
		System.out.printf("\n\n");
		
		bb.i = 30;
		bb.a = 40;
		aa.b();//a=40, i=20 另一个对象成员的值改变，不影响该类生成的其他对象
		bb.b();//a=40, i=30
		A.t();//a=40
		System.out.printf("\n\n");
		
		A.a = 60;
		A.t();//60
		aa.b();//a=60, i=20 
		bb.b();//a=60, i=30
		
	}
}
