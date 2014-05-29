//break与continue在循环中的区别 
# include <stdio.h>

int main (void)
{
    int i;
    for (i=0;i<=7;++i)
      {
         if (i == 4)
           continue ;
         else 
          printf ("%d\n",i);
      }//continue 结束本次循环 
      
      for (i=0;i<=7;++i)
      {
         if (i == 4)
           break ;
         else 
          printf ("%d\n",i);
      }//break结束全部循环 
      
    system ("pause");
    return 0;
}
