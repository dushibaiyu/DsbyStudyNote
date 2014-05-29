/*循环队列*/
# include <stdio.h>
# include <stdlib.h>

typedef struct dl
{
	int * a;
	int f;
	int t;
} DL, * PDL;

void gouzao (PDL);//构造队列 
void rudui (PDL , int);//入队 
void chudui (PDL);//出队 
bool kong(PDL);//判断是否为空 
bool isman (PDL);//判断是否已满 
void shuchu (PDL );//遍历输出 

int main (void)
{
	DL d;
	gouzao (&d);
	shuchu(&d);
	rudui(&d,10);
	rudui(&d,8);
	rudui(&d,7);
	rudui(&d,6);
	rudui(&d,5);
	rudui(&d,4);
	rudui(&d,3);
	rudui(&d,2);
	rudui(&d,1);
	rudui(&d,0);
	rudui(&d,-1);
	rudui(&d,-2);
	rudui(&d,-3);
	shuchu(&d);
	chudui(&d);
	chudui(&d);
	chudui(&d);
	shuchu(&d);
	

    system ("pause");
    return 0;
}

void gouzao (PDL p)
{
	p->a = (int *)malloc(10*sizeof(int));
	p->f = 0;
	p->t = 0;
	return ;
}

void rudui (PDL p , int i)
{
	if (isman(p))
 	{
 		printf ("队列已满,入队失败!!!\n");
 		return;
	 }
 	else
 	{
	    p->a[p->t] = i;
	    p->t = (p->t + 1)%10;
	    return ;
 	}
    
}

void chudui (PDL p)
{
	if (kong(p))
	{
		printf ("队列为空，出队失败！\n");
		return;
	}	
	else
	{
		int i = p->a[p->f];
		p->f = (p->f + 1)%10;
		printf ("出队成功！被删除的元素是：%d\n" , i);
		return ;
	}
}

bool kong(PDL p)
{
	if (p->t == p->f)
	   return true;
 	else
 		return false;
}

bool isman (PDL p)
{
	if ((p->t + 1)%10 == p->f)
		return true;
	else
		return false;
}
void shuchu (PDL p)
{
	if (kong(p))
	{
		printf ("队列为空，出队失败！\n");
		return;
	}	
	else
	{
		int i;
		for (i = p->f; i<p->t; i=(i+1)%10)
		{
			printf ("%d   ",p->a[i]);
		}
		printf("\n");	
	}
}

/* 
队列：
      定义：
            一种可以实现“先进先出”的存储结构 
      
      分类：
            链式队列  ——用链表实现 
            
            静态队列  ——用数组实现 
                   静态队列通常都是循环队列 
*/
