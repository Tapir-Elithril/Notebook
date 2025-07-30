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
    int N;
    /*the length of the list*/
    /*the integer to be found*/
    scanf("%d",&N);
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
    while(duration<=1000)/*repeat the function until the duration reaches 10 ticks*/
    {
            K++;
    /*the times the function runs*/
            start=clock();
    /*start recording the time*/
        //iterative_sequential(a,N);
        //recursive_sequential(a,N,n);
        //iterative_binary(a,N);
    /*variables defined as the parameters of the funcion recursive_binary*/
        //int low=a[0],high=a[N-1]; recursive_binary(low,high,N);
    /*delete // before the function that is going to be tested*/
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