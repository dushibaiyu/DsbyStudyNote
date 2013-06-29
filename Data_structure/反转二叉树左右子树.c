#include <stdio.h>
#include <malloc.h>

typedef struct Node
{
    int a;
    struct Node * Pleft;
    struct Node * Pright;
}NODE, * PNODE;

PNODE goujian (int);//构建二叉树,构造出满二叉树
void xianxu (PNODE);//先序遍历二叉树
void zhongxu (PNODE);//中序遍历二叉树
void fanzhuan (PNODE);//反转二叉树左右子树


int main ()
{
    PNODE p = goujian(3);//构造一个指针向根节点
    //先序便利原来的
    xianxu(p);
    printf ("\n");
    //中序便利原来的
    zhongxu(p);
    printf ("\n");
    //反转
    fanzhuan(p);

    xianxu(p);
    printf ("\n");
    zhongxu(p);
    printf ("\n");

    return 0;
}
//构建二叉数，构造出满二叉树
PNODE goujian (int b)
{
    if (0 != b)
    {
        PNODE p = (PNODE)malloc(sizeof(NODE));
        printf ("输入节点的值：");
        scanf ("%d", &p->a);
        p->Pleft = goujian(b-1);
        p->Pright = goujian(b-1);
        return p;
    }
    else
    {
        return NULL;
    }
}
//先序遍历二叉树
void xianxu (PNODE p)
{
    if (NULL == p)
    {
        return ;
    }
    else
    {
        printf ("%d  " ,p->a);
        xianxu(p->Pleft);
        xianxu(p->Pright);
        return ;
    }
}
//中序遍历二叉树
void zhongxu (PNODE p)
{
    if (NULL == p)
    {
        return ;
    }
    else
    {
        zhongxu(p->Pleft);
        printf ("%d  " ,p->a);
        zhongxu(p->Pright);
        return ;
    }
}
//反转二叉树左右子树
void fanzhuan (PNODE p)
{
    if (NULL == p)
    {
        return ;
    }
    else
    {
        PNODE t = p->Pleft;
        p->Pleft = p->Pright;
        p->Pright = t;

        fanzhuan(p->Pleft);
        fanzhuan(p->Pright);

        return;
    }
}

