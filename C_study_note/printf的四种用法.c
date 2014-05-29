/*2.10.6.19
printf的四种用法
printf（）【把值送到显示器显示】*/ 
#include<stdio.h>
int main (viod) 
{
	printf ("haha!\n");//第一种用法：printf（“字符串”）；
	int b = 10;
	int c = 20 ;
	printf ("%d\n",b) ;/*（d是十进制，b以二进制存储的，%d表示，b以什么编码格式输，
	第二种用法，printf ("输出控制符"，输出参数)； */
	 printf ("%#X  %d\n",c,b);/*o是八进制x是十六进制，第三种用法，printf ("输出控制符1 输出控制符2 ······",输出参数1,输出参数2,······)*/
	 printf ("b=%d , c=%d",c,b);//第四种用法，printf （“输出控制符 非输出控制符”，输出参数）；
	 /*%x,%X,%#x,%#X都是十六进制表示，测试程序：
	 #include<stdio.h>
	 int main ()
	 {
	    int x = 47;//编译器默认是十进制，但储存在计算机里是二进制
		printf ("x\n"'x);//输出是：2f 
		printf ("X\n"'x);//输出是：2F 
		printf ("#X\n"'x);//输出是：0X2F  %#X推荐使用 
		printf ("#x\n"'x);//输出是：0x2f
		return 0;
		}*/ 
	system ("pause");
	return 0;
}
/*为什么需要输出控制符：
  1.二进制01组成的代码可以表示数据也可以表示指令。
  2.如果01组成的代码表示的是数据的话，那么同样的01代码组合以不同的格式输出就会有不同的结果
  输出控制符包括：
   %d                  —— int 
   %ld                 —— long int 
   %c                  —— char 
   %f                  —— float 
   %lf                 —— double 
   %x(或%X,%#x,%#X )   —— int或long int ，short int 
   %o                  —— 同上 
   %s                  ——字符串 
  */
