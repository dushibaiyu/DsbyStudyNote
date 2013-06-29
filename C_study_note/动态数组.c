# include <stdio.h>
# include <malloc.h>

int main(void)
{
	//int a[5]; //如果int占4个字节的话，则本数组总共包含有20个字节，每四个字节被当做了一个int变量来使用
	int len,l;
	int * pArr;
	int i,c;

	//动态的构造一维数组
	printf("请输入你要存放的元素的个数: ");
	scanf("%d", &len);
	pArr = (int *)malloc(len * sizeof(int));  //本行动态的构造了一个一维数组, 该一维数组的元素个数（长度）是len, 该数组的数组名是pArr, 该数组的每个元素是int类型  类似于 int pArr[len];
	
	//对一维数组进行操作，  如：对动态一维数组进行赋值
	for (i=0; i<len; ++i)
	{
        printf ("给第%d元素赋值：",i+1);
		scanf("%d", &pArr[i]);
    }

	//对位一维数组进行输出
	printf("一维数组的内容是:\n");
	for (i=0; i<len; ++i)
		printf("%d\n", pArr[i]);
	printf("%#X  \n",pArr);	
	printf("请输入你新加的元素的个数: ");
	scanf("%d", &l);
	c = len + l;
	
	realloc(pArr,c* sizeof(int));//此行表示把pArr指向的地址变成 c* sizeof(int)个字节，也就是把动态数组的元素个数（长度）变成c个。 
	printf("%#X \n",pArr);	
	for (i=0; i<len; ++i)
		printf("%d\n", pArr[i]);
	if (l<0) 
	    goto a3;//goto:跳转语句，执行后程序将跳转到a3处并执行其后的语句。a3是语句标号，语句标号是一个有效的标识符,这个标识符加上一个":"一起出现在函数内某处 
	do
	{
        printf ("给新增的第%d元素赋值：",i+1);
		scanf("%d", &pArr[i]);
		i++;
    }
    while(i<c);
    a3: 
    printf("新增后一维数组的内容是:\n");
	for (i=0; i<(len+l); ++i)
		printf("%d\n", pArr[i]);
	
	free(pArr); //释放掉动态分配的数组
	
    system ("pause"); 
	return 0;
}
/*
realloc（）函数的用法：realloc（P，A） A是字节数，可以是变量，常量，和表达式。P是动态数组名即指向动态内存的指针。 
                意义：把P所指向的动态空间大小变成 A个字节。若原来是B个字节： 
                     A若大于B则保留B所储存的值。(例子中：有时可能原来值会丢失)
                     A若小于B,则保留前面A大小的值. 
*/
