#ifndef MYLIST_H
#define MYLIST_H

//#define NULL nullptr

#include <iostream>

//要抛出的异常
class mylistZeroSize{};//链表为空，也就是节点为0
class mylistMaxSize{};//要访问的数超过最大节点数

template <typename T>
struct pNode //节点数据类型
{
    T node;
    struct pNode * next;
};

template <typename T>
class mylist
{
public:
    mylist();
    ~mylist();
    mylist(const T node);
    mylist(const mylist & temp);
    void addNode(T node);//添加节点
    void showNode();//输出节点
    bool isNull()const;//判断是否为空
    T at(int i)const;//返回某个位置的值
    int size()const;//节点个数
    void clear();//清空链表

    const mylist operator=(const mylist & temp); //重载=号
    T operator[](int i)const; //重载[]

private:
    pNode<T> * pFist;
    pNode<T> * pLast;
};

using namespace std;

template <typename T>
mylist<T>::mylist(T node)
{
    pLast = new pNode<T>;
    pFist = pLast;
    pLast = new pNode<T>;
    pLast->node = node;
    pLast->next = nullptr;
    pFist->next = pLast;
}

template <typename T>
mylist<T>::mylist()
{
    pLast = new pNode<T>;
    pFist = pLast;
    pLast->next = nullptr;
}

template <typename T>
mylist<T>::mylist(const mylist &temp)
{
    pFist = new pNode<T>;
    pLast = pFist;
    pNode<T> * tp;
    for(int i = 0; i<temp.size(); ++i)
    {
        tp = pLast;
        pLast = new pNode<T>;
        pLast->node = temp.at(i);
        pLast->next = nullptr;
        tp->next = pLast;
    }
}

template <typename T>
mylist<T>::~mylist()
{
    this->clear();
    delete pFist;
    pFist = nullptr;
    pLast = pFist;
}

template <typename T>
void mylist<T>::addNode(T  node)
{
    pNode<T> * tp = pLast;
    pLast = new pNode<T>;
    pLast->node = node;
    pLast->next = nullptr;
    tp->next = pLast;
    return;
}

template <typename T>
void mylist<T>::showNode()
{
    if (this->isNull())
    {
        cout << "链表为空" <<endl;
        return;
    }

    for (int i=0; i<this->size();++i)
    {
        cout << this->at(i) <<"  ";
    }
}

template <typename T>
T mylist<T>::at(int i) const
{
    if(this->isNull())
    {
        throw mylistZeroSize();//抛出链表为空的异常
    }
    else
    {
        int j = 0;
        pNode<T> * tp = pFist->next;
        do
        {
            if (j == i)
            {
                return tp->node;
            }
            else
            {
                j++;
                tp = tp->next;
            }
        }while(tp != pLast->next);
        throw mylistMaxSize();//抛出超过最大值的异常
    }

}

template <typename T>
const mylist<T> mylist<T>::operator =(const mylist & temp)
{
    if (temp.isNull())
    {
        this->clear();
    }
    else
    {
        for (int i = 0;i<temp.size();++i)
        {
            this->addNode(temp.at(i));
        }
    }
    return *this;
}

template <typename T>
bool mylist<T>::isNull() const
{
    if(pLast == pFist)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <typename T>
int mylist<T>::size() const
{
    if(this->isNull())
    {
        return 0;
    }
    else
    {
        int j = 0;
        pNode<T> * tp = pFist->next;
        do
        {
            j++;
            tp = tp->next;
        }while(tp != pLast->next);
        return j;
    }
}

template <typename T>
void mylist<T>::clear()
{
    if (this->isNull())
    {
        return ;
    }
    else
    {
        pNode<T> * tp = pFist->next;
        pLast = pFist;
        pLast->next = nullptr;
        do
        {
            pNode<T> * tmp = tp;
            tp = tp->next;
            delete tmp;
        }while (tp != pLast->next);
    }
}

template <typename T>
T mylist<T>::operator[](int i)const
{
    return this->at(i);
}


#endif // MYLIST_H
