/*什么是素数？*/ 
# include <stdio.h>

int m(int c);
int main(void)
{
    int h;
    char ch;
    do
    {
        printf ("请输入你要判断的数:");
        scanf ("%d",&h);
        if (m(h))
           printf ("是的！素数！\n");
        else
           printf ("不是的！\n");
        printf ("还要判断吗？\n要就输入Y，不要输入任意键结束！\n");
        scanf (" %c",&ch);
    }
    while ('Y'==ch || 'y'==ch); 
     
    system ("pause");
    return 0;
} 
int m(int c)
{
    int i;
    for (i=2; i<=c;++i)
        if (c % i == 0)
          break;
    if (i == c)
       return 1;
    else
       return 0;
}
