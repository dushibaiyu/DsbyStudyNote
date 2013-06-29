/*翻转单链表
2010.10.05
自己写的，算法不严密*/
#include <stdio.h>
#include <malloc.h>

typedef struct lianbiao
{
	int a;
	struct lianbiao * next;
} LB, * PLB;

PLB gouzao (void);//构造链表 
void bianli (PLB);//遍历输出链表 
int changdu (PLB);//计算链表的有效长度 
void fanzhuan (PLB);//翻转链表  
int kong (PLB);//判断链表是否为空，

int main(void)
{
	PLB p = gouzao();
	bianli(p);
	fanzhuan(p);
	bianli(p);
	
	return 0;
}

PLB gouzao (void)//构造链表 
{
	PLB p = (PLB)malloc(sizeof(LB));//构造头结点，便于操作 
	PLB t = p;
	int i;
	t->next = NULL;
	for (i=0; i<=10; ++i)//构建有效节点并赋值 
	{
		PLB q = (PLB)malloc(sizeof(LB));
		q->a = i;
		q->next = NULL;
		t->next = q;
		t = q;
	}
	
	return p; 
}

void bianli (PLB p)//遍历输出链表 
{
	if (kong(p))
	{
		printf ("链表为空！\n");
		return;
	}
	
	PLB q = p->next;
	while (NULL != q)
	{
		printf ("%d  ",q->a);
		q = q->next;
	}
	printf ("\n");
	 
	return ;
}

int changdu (PLB p)//计算链表的有效长度 
{
	PLB q = p->next;
	int i = 0;
	while (NULL != q)
	{
		i++;
		q = q->next;
	}
	
	return i;
}

void fanzhuan (PLB p)//翻转链表 
{
	if (kong(p))
	{
		printf ("链表为空！反转失败！\n");
		return;
	}
	int i = changdu(p);
	int j = 0;
	PLB * a = (PLB *)malloc(i * sizeof(PLB));//构造指针数组，存放指向各个节点的指针 
	PLB q = p->next;
	int t;
	while (NULL != q)//把指向各节点的指针放入数组 
	{
		a[j] = q;
		q = q->next;
		j++;
	}
	for (j=0,i-=1;j<i;j++,i--)//反转，利用数组 
	{
		t = a[i]->a;
		a[i]->a = a[j]->a;
		a[j]->a = t;
	}
	free (a);
	
	return ;
}

int kong(PLB p)//判断链表是否为空，
{
	PLB q = p->next;
	if (NULL == q) 
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
