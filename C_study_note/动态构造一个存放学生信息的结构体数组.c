/*动态构造一个存放学生信息的结构体数组
英语学得不好，变量名都是拼音首字母*/
# include <stdio.h>
# include <malloc.h>

struct xs
{
       char mz[100];
       int xh;
       float fs;
};

void sr (struct xs * ,int );
void px (struct xs * ,int );
void sc (struct xs * ,int );

int main (void)
{
    char ch;
    int s;    
    printf ("请输入学生数：");
    scanf ("%d",&s); 
    while ( (ch=getchar()) !='\n')
         continue;
    struct xs * p = (struct xs *)malloc(s*sizeof(struct xs ));
    
    sr (p,s);
    px (p,s);
    sc (p,s);
    free (p);
    system ("pause");//dev c++编译的，需要这个语句防止一闪而过。 
    return 0;
}

void sr (struct xs * q,int h)//输入 
{
     int i;
     char ch;
     for (i=0;i<h;++i)
    {
        printf ("第%d个学生的信息：\n",i+1);
        printf ("学号是：");
        scanf ("%d",&q[i].xh);
        while ( (ch=getchar()) !='\n')
              continue;
        printf ("姓名是：");
        scanf ("%s",q[i].mz);//不加取地址符。mz是数组名，数组名存放的是数组首元素的地址 
        while ( (ch=getchar()) !='\n')
              continue;
        printf ("分数是：");
        scanf ("%f",&q[i].fs);
        while ( (ch=getchar()) !='\n')
              continue;
    }
    return ;
}

void px (struct xs * q,int h)//排序 
{
     struct xs t;
     int i,j;
     for (i=0; i<h-1; ++i)
     {
         for (j=0; j<h-1-i; ++j)
         {
             if (q[j].fs < q[j+1].fs)
             {
                t = q[j];
                q[j] = q[j+1];
                q[j+1] = t;
             }
         }
     }
     return ;
}

void sc (struct xs * q,int h)//输出 
{
     int i;
     for (i=0; i<h; i++)
         printf ("%d  %s  %f\n",q[i].xh,q[i].mz,q[i].fs);
         
     return ;
}
