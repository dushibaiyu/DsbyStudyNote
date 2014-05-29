# include <stdio.h>
# include <malloc.h>  //包含了malloc函数
# include <stdlib.h>  //包含了exit函数,和system函数 

//定义了一个数据类型，该数据类型的名字叫做struct Arr, 该数据类型含有三个成员，分别是pBase, len, cnt
struct Arr
{
	int * pBase; //存储的是数组第一个元素的地址
	int len; //数组所能容纳的最大元素的个数
	int cnt; //当前数组有效元素的个数
};

void init_arr(struct Arr * pArr, int length); //初始化数组 
bool append_arr(struct Arr * pArr, int val); //追加元素 
bool insert_arr(struct Arr * pArr, int pos, int val); //数组中插入值
bool delete_arr(struct Arr * pArr, int pos, int * pVal);//删除 
int get();
bool is_empty(struct Arr * pArr);//判断数组是否为空 
bool is_full(struct Arr * pArr);//判断数组是否已满 
void sort_arr(struct Arr * pArr);//给数组排序 
void show_arr(struct Arr * pArr); //输出数组 
void inversion_arr(struct Arr * pArr);//把数组倒置 

int main(void)
{
	struct Arr arr;
	int val;
	
	init_arr(&arr, 6);
	show_arr(&arr);
	append_arr(&arr, 1);
	append_arr(&arr, 10);
	append_arr(&arr, -3);
	append_arr(&arr, 6);
	append_arr(&arr, 88);
	append_arr(&arr, 11);
	if ( delete_arr(&arr, 4, &val) )
	{
		printf("删除成功!\n");
		printf("您删除的元素是: %d\n", val);
	}
	else
	{
		printf("删除失败!\n");
	}
/*	append_arr(&arr, 2);
	append_arr(&arr, 3);
	append_arr(&arr, 4);
	append_arr(&arr, 5);
	insert_arr(&arr, -1, 99);
	append_arr(&arr, 6);
	append_arr(&arr, 7);
	if ( append_arr(&arr, 8) )
	{
		printf("追加成功\n");
	}
	else
	{
		printf("追加失败!\n");
	}
*/	
	show_arr(&arr);
	inversion_arr(&arr);
	printf("倒置之后的数组内容是:\n");
	show_arr(&arr);
	sort_arr(&arr);
	show_arr(&arr);

	//printf("%d\n", arr.len);

    system("pause");
	return 0;
}

void init_arr(struct Arr * pArr, int length)
{
	pArr->pBase = (int *)malloc(sizeof(int) * length);//分配动态内存，构成数组 
	if (NULL == pArr->pBase)//判断是否分配成功 
	{
		printf("动态内存分配失败!\n");
		exit(-1); //终止整个程序
	}
	else
	{
		pArr->len = length;//确定数组的最大能容纳的元素个数。 
		pArr->cnt = 0;//确定有效元素个数，因为还都没初始化赋值，所以为0 
	}
	return;
}

bool is_empty(struct Arr * pArr)//判断数组是否为空 
{
	if (0 == pArr->cnt)//判断元素有几个有效元素 
		return true;//若为零则为空数组 
	else
		return false;		
}

bool is_full(struct Arr * pArr)//判断数组是否已满 
{
	if (pArr->cnt == pArr->len)//判断是否有效元素等于最大元素相等 
		return true;//相等则满了，返回真 
	else
		return false;
}

void show_arr(struct Arr * pArr)//输出数组
{
	if ( is_empty(pArr) )   
	{
		printf("数组为空!\n");
	}
	else
	{
		for (int i=0; i<pArr->cnt; ++i)
			printf("%d  ", pArr->pBase[i]); //输出数组各元素内容 
		printf("\n");
	}
}

bool append_arr(struct Arr * pArr, int val)//给数组追加值 
{
	if ( is_full(pArr) )//判断数组是否已满，若满就不能在追加了，返回false
		return false;

	//不满时追加
	pArr->pBase[pArr->cnt] = val; //有效元素是pArr->cnt个，所以数组的下标就是0~（pArr->cnt-1） ，所以要追加元素的下标也就是pArr->cnt 
	(pArr->cnt)++;//因为数组又追加了一个元素，所以有效元素pArr->cnt 也应该相应加一。 
	return true;
}

bool insert_arr(struct Arr * pArr, int pos, int val)//在第pos个元素的前面插入val的值 
{
	int i;

	if (is_full(pArr))
		return false;

	if (pos < 1 || pos > pArr->cnt+1)//判断输入的pos是否合法 ，pos的值从1开始，最大不能超过数组所能储存的最大个数。 
		return false;

	for (i = pArr->cnt-1; i >= pos-1; --i)//叫插入位置后的数组元素向后移，为要插入元素腾出位置。 
	{
		pArr->pBase[i+1] = pArr->pBase[i];//要把前面的值赋给后面的 
	}
	pArr->pBase[pos-1] = val;//把要插入的值插入腾出的空间。 
	(pArr->cnt)++;//中间插入了数据，有效值相应增加·· 
	return true;
}

bool delete_arr(struct Arr * pArr, int pos, int * pVal)//删除第pos个元素前的值，并返回所删除值的内容 
{
	int i;

	if ( is_empty(pArr) )//判断是否为空数组， 
		return false;//若为空就会无法执行删除，结束此函数并返回错误值 
	if (pos<1 || pos>pArr->cnt)//判断pos是否合法，元素排序是1~pArr->cnt个，所以应大于1不大于pArr->cnt 
		return false;//若不合法，就无法执行删除，结束函数，并返回错误值。 

	*pVal = pArr->pBase[pos-1];//先保存要删除的值 
	for (i=pos; i<pArr->cnt; ++i)
	{
		pArr->pBase[i-1] = pArr->pBase[i]; 
	}//执行删除.把要删除的元素后的元素前移（这样就把要删除的值组东覆盖了。），
	pArr->cnt--;//因为数组中元素被删除一个，所以有效元素就少一个 
	return true;
}

void inversion_arr(struct Arr * pArr)//把数组元素倒置 
{
	int i = 0;
	int j = pArr->cnt-1;
	int t;

	while (i < j)
	{
		t = pArr->pBase[i];
		pArr->pBase[i] = pArr->pBase[j];
		pArr->pBase[j] = t;
		++i;
		--j;
	}
	return;
}

void sort_arr(struct Arr * pArr)//给元素从小到大排序 
{
	int i, j, t;

	for (i=0; i<pArr->cnt; ++i)
	{
		for (j=i+1; j<pArr->cnt; ++j)
		{
			if (pArr->pBase[i] > pArr->pBase[j])
			{
				t = pArr->pBase[i];
				pArr->pBase[i] = pArr->pBase[j];
				pArr->pBase[j] = t;
			}
		} 
	}
	return ; 
}
