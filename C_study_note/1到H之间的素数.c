//求1到n之间的素数 
int m(int c);
int main(void)
{
    int h,i,j=0;
    scanf ("%d",&h); 
    
    for (i=2; i<=h; ++i)
    {
        if (m(i))
        {
          printf (" %d ",i);
          j++;
        }
    }
    printf ("\n\n1到%d之间一共有%d个素数。\n\n",h ,j);

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
