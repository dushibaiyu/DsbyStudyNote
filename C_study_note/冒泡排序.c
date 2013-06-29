/*ц╟ещеепР*/
# include <stdio.h>

void sort (int * ,int);
void sc (int * , int);

int main (void)
{
    int a[6] = {5,0,-23,568,97,7};
    
    sc (a,6);
    
    sort (a,6);
    
    sc (a,6);
    
    system ("pause"); 
    return 0;
}
void sort (int * p ,int a)
{
   int i,j,t;
   for (i=0; i<a-1; ++i) 
   {
      for (j=0;j<a-1-i; ++j) //0~4
      {
          if (p[j] > p[j+1])
          {
             t = p[j];
             p[j] = p[j+1];
             p[j+1] = t;
          }
      }
   }
   return ; 
}
void sc (int * p,int a)
{
     int i;
     for (i=0; i<a ; ++i)
        printf ("%d   ", p[i]);
     printf ("\n");
     return ;
}
