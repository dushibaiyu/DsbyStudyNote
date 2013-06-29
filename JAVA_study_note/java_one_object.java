//一个类只生成一个对象,java表示
//注：java中无参数的的函数不能用yy（void）形式
class A
{
	public int i;

	private static A aa = new A();//在类中生成一个对象。aa只是引用（C/C++中指针），一个指向该类类型的一快内存，对象在堆中分配
								//设置成私有为了保护成员，防止不小心破坏结构
	public static A getA()//该函数必须设成静态的，和公共的，保证在类外能访问，而且不能属于对象。
	{
		return aa;//返回在类中生成的引用地址，这样在类外也能访问在类中生成的那个对象
	}
	private A(){}//把构造函数设置成私有的，外部就不可以访问，也就没发直接定义该类的对象
}

class java_one_object
{
	public static void main (String[] args)
	{
		//A aa = new A();//错误，类的构造函数是私有的，类外不可访问
		A aa = A.getA();//把在类中生成的对象的地址赋给aa
		A bb = A.getA();//把在类中生成的对象的地址赋给bb,此时aa和bb相等
		
		if(aa == bb)
		{
			System.out.printf ("aa = bb\n");
		}
		else 
		{
			System.out.printf ("aa != bb\n");
		}
		
		aa.i = 100;
		System.out.printf ("aa.i=%d  bb.i=%d\n",aa.i,bb.i);
	}
}