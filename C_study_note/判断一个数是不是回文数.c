# include <stdio.h> 

int main (void)
{
    int val, m, sum=0;
    printf ("请输入你要判断的整数！\n");
    scanf ("%d",&val); 
    
    m = val;
    while (m)
    {
          sum = sum * 10 + m % 10;
          m/=10; 
    }
    /*试数：算法的流程： 
    设m=123
    m % 10 =3，sum = 3,->m /10=12->（m=12，m！=0进入下次循环 ） 
    m % 10 =2，sum = 32,->m /10=1->（m=1,m！=0进入下次循环 ）
    m % 10 =1，sum = 321,->m /10=0->（m=0终止循环 ）
    */
 
    if (sum == val)  
      printf ("这个数是回文数！\n");
    else
      printf ("这个数不是回文数\n");
    
    system ("pause");
    return 0;
}
