#include<stdio.h>
#include<stdlib.h>
/*we need to use the function malloc*/
#include "tree.h"
/*a function library storing the functions needed in the main.c*/
int del;
/*used for deleting repeated equations*/
int main(int argc,char *argv[])
{
    FILE *file=fopen("result.txt","w");
    /*print the result in result.txt*/   
    int n1,n2,i,N;
    scanf("%d",&n1);
    int a[n1][2];
    /*defining a 2D array for inputting
    the first column stores the element
    the second column stores the parent_index*/
    for(i=0;i<n1;i++)
    {
        scanf("%d %d",&a[i][0],&a[i][1]);
    }
    Tree T1=BuildTree(n1,a);
    /*build tree through recursive method*/
    del=T1->Element;
    scanf("%d",&n2);
    int b[n2][2];
    for(i=0;i<n2;i++)
    {
        scanf("%d %d",&b[i][0],&b[i][1]);
    }
    Tree T2=BuildTree(n2,b);
    scanf("%d",&N);
    FindNumber(N,T1,T2,del,file);
    /*function used for find whether N can be written as A+B
    where A is in Tree T1 and B is in Tree T2
    if N can be written as A+B print true and all the equation N=A+B*/
    Preorder(T1,n1,file);
    /*Preorder traversal of T1 
    print the elements of T1 in preorder*/
    Preorder(T2,n2,file);
    return 0;
}