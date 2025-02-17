#include "main.h"
/*process the 4 programmes written in the main.h*/
#include<stdio.h>
#include<time.h>
int main(int argc,char *argv[])
/*this is the main programme used for testing the time of the 4 programmes*/
{
    clock_t start,stop;
    double duration=0;
    /*setting the variables for recording the time*/
    int N,j,ticks;
    /*the length of the list*/
    /*the integer to be found*/
    /*the function to be tested*/
    scanf("%d %d %d",&N,&j,&ticks);
    if(j!=0&&j!=1&&j!=2&&j!=3){printf("invalid input");return 0;}
    int n=N;
    /*used for creating a[n]*/
    /*this N is used for the 4 programmes
    helping to compare the differences of time under the same N*/
    int i,a[n];
        for(i=0;i<n;i++)
    {
        a[i]=i;
    }
    /*create a list of number from 0——N-1*/
    int K=1;/*used from record the times of repetition*/
    while(duration<=ticks)/*repeat the function until the duration reaches adequate ticks*/
    {
            K++;
    /*the times the function runs*/
            start=clock();
    /*start recording the time*/
    /*use function switch to select the function that is to be tested*/
    	switch (j)
	{
		case 0:iterative_sequential(a,N);break;
		case 1:recursive_sequential(a,N,n);break;
		case 2:iterative_binary(a,N);break;
		case 3:int low=a[0],high=a[N-1]; recursive_binary(low,high,N);break; /*variables defined as the parameters of the funcion recursive_binary*/
	}
            stop=clock();
    /*stop recording the time*/
            duration+=(stop-start);
    }
    /*processing the 4 functions under the same N
    and get the times used for each processing */
    /*according to the test on time.h CLK_TCK=1000*/
    duration=duration/CLK_TCK;
    /*calculate the time spent running the programme(unit:sec)*/
    printf("%d %lf",K,duration);
    return 0;
}