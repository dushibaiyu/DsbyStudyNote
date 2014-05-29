//排序算法之：快速排序
#include <iostream>
#include <vector>

using namespace std;

void quickSort(vector<int> & tmp, int left, int rigth);

int main()
{

    vector<int> tp;
    tp.push_back(2);
    tp.push_back(30);
    tp.push_back(-20);

    quickSort(tp,0,tp.size()-1);

    for(unsigned int i=0; i<tp.size();++i)
    {
        cout << tp.at(i) << "  ";
    }

    cout << endl << "Hello World!" << endl;
    return 0;
}

int cutFun(vector<int> & tmp,int left,int rigth)
{
    //首先挑选一个基准元素
    int base = tmp.at(left);
    while (left < rigth)
    {
        //从数组的右端开始向前找，一直找到比base小的数字为止(包括base同等数)
        while (left < rigth && tmp.at(rigth) >= base )
                rigth --;
         //最终找到了比baseNum小的元素，要做的事情就是此元素放到base的位置
        tmp.at(left) = tmp.at(rigth);

        //从数组的左端开始向后找，一直找到比base大的数字为止（包括base同等数）
        while(left < rigth && tmp.at(left) <= base)
            left ++;
         //最终找到了比baseNum大的元素，要做的事情就是将此元素放到最后的位置
        tmp.at(rigth) = tmp.at(left);
    }
    //最后就是把baseNum放到该left的位置
    tmp.at(left) = base;

    //最终，我们发现left位置的左侧数值部分比left小，left位置右侧数值比left大
    //至此，我们完成了第一篇排序
    return left;
}

void quickSort(vector<int> & tmp,int left,int rigth)
{
    //左下标一定小于右下标，否则就超越了
    if (left < rigth)
    {
        //对数组进行分割，取出下次分割的基准标号
        int t = cutFun(tmp,left,rigth);
        //对“基准标号“左侧的一组数值进行递归的切割，以至于将这些数值完整的排序
        quickSort(tmp,left,t-1);
        //对“基准标号“右侧的一组数值进行递归的切割，以至于将这些数值完整的排序
        quickSort(tmp,t+1,rigth);
    }
}

/*
 *  20 , 40 , 50 , 10 , 60 ;      20
 * left                rigth     base
 * left指针，right指针，base参照数。
其实思想是蛮简单的，就是通过第一遍的遍历（让left和right指针重合）来找到数组的切割点。

第一步：首先我们从数组的left位置取出该数（20）作为基准（base）参照物。

第二步：从数组的right位置向前找，一直找到比（base）小的数，

            如果找到，将此数赋给left位置（也就是将10赋给20），

            此时数组为：10，40，50，10，60，

            left和right指针分别为前后的10。

第三步：从数组的left位置向后找，一直找到比（base）大的数，

             如果找到，将此数赋给right的位置（也就是40赋给10），

             此时数组为：10，40，50，40，60，

             left和right指针分别为前后的40。

第四步：重复“第二,第三“步骤，直到left和right指针重合，

             最后将（base）插入到40的位置，

             此时数组值为： 10，20，50，40，60，至此完成一次排序。

第五步：此时20已经潜入到数组的内部，20的左侧一组数都比20小，20的右侧作为一组数都比20大，

            以20为切入点对左右两边数按照"第一，第二，第三，第四"步骤进行，最终快排大功告成。

*/
