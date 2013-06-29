/*三木运算符与逗号表达式；
*/
# include <stdio.h>
int main (viod)
{
    int i,a,j=0; 
    i = (1<2 ? 5 : 2); 
    printf ("i=%d\n",i);
    a = (1,45,j++,j--,45,10,j-1);
    printf ("j=%d\na=%d\n",j,a);
    system ("pause");
    return 0;
}
/*三目运算符
A?B:C
等价于：
 if （Ａ）
 　　Ｂ
 else
     C 
 逗号表达式：
  （A,B,C,D······）
  功能：从左到右执行，最终表达式的值是最后一项。 
*/
