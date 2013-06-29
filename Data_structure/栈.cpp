/*栈*/
# include <stdio.h>
# include <stdlib.h>
# include <malloc.h>

typedef struct node
{
	char a[10];
	int date;
	struct node * next;
}NODE, * PNODE;

typedef struct storck
{
	PNODE ptop;
	PNODE pbottom;
}STORCK, * PSTORCK;

STORCK goujian (void);//构建栈 
void bianli (PSTORCK);//遍历输出 
int kong (PSTORCK);//判断是否为空 
void zhujia (PSTORCK);//压栈 
int shanchu (PSTORCK, PNODE);//出栈 
void qingkong (PSTORCK);//清空栈 

int main (void)
{
	STORCK a = goujian();
	PSTORCK p = &a;
	NODE h;
	int i;
	
	bianli(p);
	zhujia(p);
	zhujia(p);
	zhujia(p);
	i = shanchu(p,&h);
	if (i)
	{
		printf("被删除的元素内容是：%s   %d\n",h.a, h.date);
	}
	else
	{
		printf ("栈为空，删除失败！\n"); 
	} 
	bianli(p);
	qingkong(p);
	bianli(p); 
	
	return 0;
}

STORCK goujian (void)
{
	STORCK a;
	a.ptop = (PNODE)malloc(sizeof(NODE));
	a.ptop->next = NULL;
	a.pbottom = a.ptop;
	return a;
}

void bianli (PSTORCK p)
{
	if (kong(p))
	{
		printf ("你要输出的栈为空！！\n");
	}
	else
	{
		int i=0;
		PNODE q = p->ptop;
		while (p->pbottom != q)
		{
			printf ("第%d个元素是：",i+1);
			printf ("%s   %d\n",q->a,q->date);
			q = q->next;
			++i;
			
		}
	} 
	return ;
}

int kong (PSTORCK p)
{
	if (p->ptop == p->pbottom)
	{
		return 1;
	}
	else 
	{
		return  0;
	}
}

void zhujia (PSTORCK p)
{
	PNODE q = (PNODE)malloc(sizeof(NODE));
	printf ("请输入名字：");
	scanf ("%s",q->a);
	printf ("请输入学号：");
	scanf ("%d",&q->date);
	q->next = p->ptop;
	p->ptop = q;
	 
	return ;
}

int shanchu (PSTORCK p, PNODE q)
{
	if(kong(p))
	{
		return 0;
	}
	
	PNODE r = p->ptop;
	*q = *r;
	p->ptop = r->next;
	free(r);
	return 1 ;
}

void qingkong (PSTORCK p)
{
	PNODE q ;
	while (p->ptop != p->pbottom)
	{
		q = p->ptop;
		p->ptop = q->next;
		free(q);
	}
	return;
}



/*
栈：
  定义：
        一种可以实现先进后出的存储结构
        栈类似于箱子 
  分类：
        静态栈
        
        动态栈 （本质是一个操作受限的链表） 
               
  算法：
        出栈
        压栈（入栈） 
  
  应用：
   
*/
