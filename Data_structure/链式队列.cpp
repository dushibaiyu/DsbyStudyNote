/*链式队列*/
# include <stdio.h> 
# include <malloc.h>
#include <stdlib.h>

typedef struct node
{
	int a;
	struct node * next;
}NODE, *PNODE;

typedef struct  dl
{
	PNODE front;
	PNODE rear;
}DL, * PDL;

DL gz(void);
bool kong (PDL);
void bl (PDL);
void rd (PDL, int);
void cd (PDL);

int main (void)
{
	DL d = gz();
	PDL p = &d;
	bl(p);
	
	rd(p,10);
	rd(p,9);
	rd(p,8);
	rd(p,7);
	rd(p,6);
	rd(p,5);
	rd(p,4);
	rd(p,3);
	rd(p,2);
	rd(p,1);
	bl(p);
	
	cd(p);
	cd(p);
	cd(p);
	bl(p);
	
	cd(p);
	cd(p);
	cd(p);
	cd(p);
	cd(p);
	cd(p);
	cd(p);
	cd(p);
	bl(p);
	
	system ("pause");
	return 0;
}

DL gz(void)//构造队列头结点 
{
	DL h;
	PNODE p = (PNODE)malloc(sizeof(NODE));
	p->next = NULL;
	h.front = p;
	h.rear = p;
	return h;
}

bool kong (PDL p)//判断队列是否为空 
{
	PNODE q = p->front->next;
	if (NULL == q)
		return true;
	else
		return false;
}

void bl (PDL p)//遍历输出队列 
{
	if (kong(p))
	{
		printf ("队列为空！\n");
		return ;
	}
	
	PNODE q = p->front->next;
	while (q != NULL)
	{
		printf ("%d   ",q->a);
		q = q->next;
	}
	printf ("\n");
	return ;
}

void rd (PDL p, int i)//入队 
{
	PNODE q = (PNODE)malloc(sizeof(NODE));
	q->a = i;
	q->next = NULL;
	p->rear->next = q;
	p->rear = q;
	return;
}//入队在队尾，新增尾节点 

void cd (PDL p)//出队 
{
	if (kong(p))
	{
		printf ("队列为空，出队失败！！！\n");
		return ;
	}
	else
	{
		int i;
		PNODE q = p->front->next;
		p->front->next = q->next;
		i = q->a;
		free(q);
		printf ("出队成功，你出队的元素是：%d\n",i);
		return ;
	}
}//再对头，出首节点 
/*
此队列的样式是：
 ∞→∞→∞→∞→``````→∞
↑ 						 ↑
front					rear
头结点					rear->next == NULL 
（不存放有效值） 
*/