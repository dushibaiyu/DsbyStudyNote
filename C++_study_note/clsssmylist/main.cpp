#include <iostream>
#include "mylist.h"

using namespace std;

int main()
{

    cout << "hello mylist!" <<endl;
    mylist<int> mlist;
    cout << mlist.size()<<endl;
    for(int i = 0; i<=5; ++i)
    {
        mlist.addNode(i);
    }
    cout << mlist.size()<<endl;
    mlist.showNode();
    cout <<endl;

    cout <<"重载[]:"<< mlist[0]<<endl;


    mylist<int> nlist(mlist);
    cout << nlist.size()<<endl;
    mlist.clear();
    cout << mlist.size()<<endl;

    nlist.showNode();
    cout << endl;

    mylist<int> list = nlist;
    list.showNode();
    cout << endl;

    cout << list.at(10)<<endl;

    list = mlist;
    cout << list.size()<<endl;

    return 0;
}

