#include <stdio.h>
int main ()
{
	float score;//score:分数
	printf ("请输入成绩！\n") ;
	scanf ("%f",&score);
	if (score>100)
	  printf ("你在白日做梦啊！\n");
    else if (score>=90&&score<=100) /*不可写成90>=score=<100 ，
	因为程序由左到右执行，score的结果是1或0，永远小于100，恒成立了！ */ 
      printf ("恭喜你！成绩很好！优秀！\n");
	else if (score>=80&&score<=90) 
	  printf ("优秀！但还有进步的余地！\n");
    else if (score>=70&&score<=80)
      printf ("良好！还要继续努力啊！\n");
    else if (score>=60&&score<=70)
      printf ("及格！还要加倍努力啊！\n");
    else if (score<0)
	  printf ("你小子不行啊！还能得负数？\n"); 
	else
	  printf ("还不及格啊！多多努力啊！\n");

    system ("pause");	
   return 0;
}
