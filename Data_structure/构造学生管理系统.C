# include <stdio.h>
# include <stdlib.h>
# include <malloc.h>

typedef struct xuesheng //定义链表的结点 
{
	char xm[10];
	int xh;
	float fs;
	struct xuesheng * next;
}XS,* PXS;
char ch;

PXS gouzao (void);//构造这个链表 
void shuru(PXS);//输入有效值 
int changdu(PXS);//求链表的长度 
void Fpaixu(PXS, int); //按分数排序 
void Xpaixu(PXS, int);//按学号排序 
void shuchu(PXS);//输出链表内容 

int main (void)
{
	PXS p;
	int a;
	
	p = gouzao();
	shuru(p);
	a = changdu(p);
	if(a > 0)
	{
    int i;
al:	printf ("请选择你要的排序方式：\n1.分数从大向小排序\n2.按学号从小到大排序\n输入序号选择：");
	  scanf ("%d",&i);
	  switch(i)
	  {
	  	case 1:
	  		Fpaixu(p,a);
	  		break;
	  	case 2:
	  		Xpaixu(p,a);
	  		break;
	  	default:
	  		printf ("输入错误！请重新选择！\n");
	  		goto al;
	  }  
	  shuchu(p);
	}
	else
		printf ("学生为零，无需管理！\n");

	
	system ("pause");
	return 0;
}

PXS gouzao (void)//构造链表 
{
	int a,i;
	
	PXS p = (PXS)malloc(sizeof(XS));//构造头结点 
	if (p == NULL)
	{
		printf ("内存分配失败！程序结束！\n");
		exit (-1);
	}
	
	PXS q = p;
	q->next = NULL;
	
	printf ("请输入班级的现有人数：");
	scanf ("%d",&a);
	while ((ch=getchar()) != '\n')
		     continue;
	
	for (i=0; i<a ;++i)	//按长度构造链表 
	{
		PXS pn = (PXS)malloc(sizeof(XS));
		if (pn == NULL)
		{
			printf ("内存分配失败！程序结束！\n");
			exit (-1);
		}
		q->next=pn;
		pn->next = NULL;
		q=pn;
	}
	
	return p;
}

void shuru(PXS q)//给链表赋值 
{
	int i=1;
	PXS p= q->next;
	while(p != NULL)
	{
		printf ("请输入第%d个学生的姓名：",i);
		scanf ("%s",p->xm);
		while ((ch=getchar()) != '\n')
		     continue;
		printf ("请输入第%d个学生的学号：",i);
		scanf ("%d",&p->xh);
		while ((ch=getchar()) != '\n')
		     continue;
		printf ("请输入第%d个学生的分数：",i);
		scanf ("%f",&p->fs);
		while ((ch=getchar()) != '\n')
		     continue;
		p=p->next;
		++i;         
	}
	
	return ;
}

int changdu(PXS q)
{
	int a=0;
	PXS p=q->next;
	while(p != NULL)
	{
		a++;
		p = p->next;
	}
	
	return a;
}

void Fpaixu(PXS q, int a)
{
	int j,i;
	XS t;
	PXS h,g;
	PXS p=q->next;
	for (i=0; i<a-1; ++i,p=p->next)
	{
		for(j=i+1,q=p->next; j<a; ++j,q=q->next)
		{
			if (p->fs < q->fs)
				{
				    h = p->next;
            g = q->next;
                    
					t = *p;
					*p = *q;
					*q = t;
					
					p->next = h;
					q->next = g;
				}
		}
	}
	
	return;
}

void Xpaixu(PXS q,int a)
{
	int j,i;
	XS t;
	PXS h,g;
	PXS p=q->next;
	for (i=0; i<a-1; ++i,p=p->next)
	{
		for(j=i+1,q=p->next; j<a; ++j,q=q->next)
		{
			if (p->xh > q->xh)
				{
				    h = p->next;
            g = q->next;
                    
					t = *p;
					*p = *q;
					*q = t;
					
					p->next = h;
					q->next = g;
				}
		}
	}
	
	return;
}

void shuchu(PXS q)
{
	PXS p=q->next;
	int i=1;
	while (p != NULL)
	{
		printf ("第%d个学生：\n学号：%d   姓名：%s    分数：%f\n",i,p->xh,p->xm,p->fs);
		++i;
		p = p->next;
	}
	printf ("一共%d个学生！\n",i);
	
	return;
}
