
 
class cat
{
//private私有成员；只允许本类中的函数访问
	private String name;
	private String color;
	private int age;
//protected保护成员，Java中保护成员自啊类外也可以访问，和C++不同
	protected  String from;
// public是公有成员（外部接口），在类外可以访问。
	public cat(String a, String b, int i, String c)
	{
		name = a ; color = b ; age = i ; from = c;
	}
	public cat(){}
	public void initialize (String a, String b, int i, String c)//初始化
	{
		name = a ; color = b ; age = i ; from = c;
		return ;
	}
	public void print ()//打印 输出
	{
		System.out.printf("Name is %s\nColor is %s\nAge is %s\n Form for %s.",name , color , age, from);
		return ;
	}
}; 

class java访问控制1
{
	public static void main(String[] args)
	{
		cat i = new cat("name", "red", 2, "china");//在堆中动态分配对象i；并用构造函数给其初始化。
		i.print();//public能在类外访问
		// i.name = "hello" ;//错误，private(私有)不能在类外访问
		i.from = "USA" ; //正确，这个C++中不同，C+中保护成员同样不能在类外访问，java能。
		i.print();
		return ;
	}
}

/* 
Java中访问修饰符的书写方法和C++不同。声明访问控制符的没有顺序
Java的：
class 类名
{
	private 成员说明;//私有成员 ；只允许本类中的函数访问
	private 成员说明;
	······ //每个成员都要单独加上控制符
	
	protected 成员说明; //保护成员 ；Java中保护成员自啊类外也可以访问，和C++不同
	protected 成员说明; 
	······//每个成员都要单独加上控制符
	
	public 成员说明;//公有成员； （外部接口），在类外可以访问。
	public 成员说明;
	······//每个成员都要单独加上控制符
};

*/
/*
C++的
class 类名称
		{
			public://以下都是公有成员，直到类声明结束或遇到下个访问控制符，冒号(:)不可省
					公有成员（外部接口）；//任何外部函数都可以访问。
			private:    //如果紧跟类名称后面声明私有成员，关键字private可以省略。以下都是私有成员，直到类声明结束或遇到下个访问控制符，冒号(:)不可省
					私有成员；  //只允许本类中的函数访问。
			protected://以下都是保护成员，直到类声明结束或遇到下个访问控制符，冒号(:)不可省
					保护型成员；  //与private相似，类外不可访问，差别在继承和派生时对派生类的影响不同。
		} ；
 */
