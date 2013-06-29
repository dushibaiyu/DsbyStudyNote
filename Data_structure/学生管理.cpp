# include <stdio.h>
# include <stdlib.h>
# include <malloc.h>

typedef struct xuesheng 
{
	char xm[10];
	int xh;
	float fs;
	struct xuesheng * next;
}XS,* PXS;
char ch;

PXS gouzao (void);
int changdu(PXS);
void Fpaixu(PXS, int); 
void Xpaixu(PXS, int);
void shuchu(PXS);

int main (void)
{
	PXS p;
	int a;
	
	p = gouzao();
	a = changdu(p);
	
	if(a > 0)
	{
	  int i;
al:	  printf ("请选择你要的排序方式：\n1.分数从大向小排序\n2.按学号从小到大排序\n输入序号选择：");
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

PXS gouzao (void)
{
	int a,i;
	XS t;
	
	PXS p = (PXS)malloc(sizeof(XS));
	if (p==NULL)
	{
		printf ("内存分配失败！程序结束！\n");
		exit (-1);
	}
	
	printf ("请输入班级的现有人数：");
	scanf ("%d",&a);
	while ((ch=getchar()) != '\n')
		     continue;
	
	PXS q = p;
	q->next = NULL;
	
	for (i=0; i<a ;++i)	
	{
		PXS pn = (PXS)malloc(sizeof(XS));
		if (pn==NULL)
		{
			printf ("内存分配失败！程序结束！\n");
			exit (-1);
		}
		printf ("请输入第%d个学生的姓名：",i+1);
		scanf ("%s",t.xm);
		while ((ch=getchar()) != '\n')
		     continue;
		printf ("请输入第%d个学生的学号：",i+1);
		scanf ("%d",&t.xh);
		while ((ch=getchar()) != '\n')
		     continue;
		printf ("请输入第%d个学生的分数：",i+1);
		scanf ("%f",&t.fs);
		while ((ch=getchar()) != '\n')
		     continue;
		t.next = NULL;
		*pn = t;
		q->next=pn;
		q=pn;
	}
	
	return p;
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
	int i=0;
	while (p != NULL)
	{
		printf ("第%d个学生：\n学号：%d   姓名：%s    分数：%f\n",i+1,p->xh,p->xm,p->fs);
		++i;
		p = p->next;
	}
	printf ("一共%d个学生！\n",i);
	
	return;
}
