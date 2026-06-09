#include<stdio.h>
#include<time.h>
/*test the time complexity by calculating the total time of running the programme for K times*/
int iterative_sequential(int a[],int N)
{
    int i;
    for (i=0;i<N;i++) /*the iterative method used to find N*/
    /*traversal the list and judge whether N is in the list*/
    {
        if(i==N)
        {return 1;}
    /*if N is found in the list end the programme by return 0*/
    }
    return 0;
    /*if N is not found in the list end the programme by return -1*/
}

int recursive_sequential(int a[],int N,int n)
{
    if(a[N]==0&&n!=a[N]){return 0;}
    /*if N is not found through the whole list,return 0*/
    if(n!=a[N-1]){return recursive_sequential(a,N-1,n);}
    /*search N in the list through recursion*/
    if(n==a[N-1]){return 1;}
    /*if N is found,return 1*/
}

int iterative_binary(int a[],int N)
{
    int low=a[0],high=a[N-1];
    int mid=(low+high)/2;
    /*define low high mid for comparison*/
    while(mid!=high&&mid!=low)
    {
    if(a[mid]==N){return 1;}
    if(a[mid]<N){low=mid;mid=(low+high)/2;}
    if(a[mid]>N){high=mid;mid=(low+high)/2;}
    }
    /*use while to judge whether a[mid] is equal to N
    if a[mid] equals N return 1
    else change mid according to the volume of a[mid] and N*/
    return 0;
}

int recursive_binary(int low,int high,int N)
{
    int mid=(low+high)/2;
    if(low==mid||mid==high){return 0;}
    /*function reached end by returning 0*/
    if(mid==N){return 1;}
    if(mid<N){return recursive_binary(mid,high,N);}
    if(mid>N){return recursive_binary(low,mid,N);}
    /*cut the list by half through recursion*/
}

