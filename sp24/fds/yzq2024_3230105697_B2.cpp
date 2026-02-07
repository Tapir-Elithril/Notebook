/* Author: Yang YiChou;  ID: 3230105697;  No.02 */
#include<stdio.h>
#define INTMAX 2147483647
int heap[50001];
void perculatedown(int heap[],int i,int M)
{
    int child;
    int temp;
    for(temp=heap[i];2*i+1<M;i=child)
    {
        child=2*i+1;
        if(child!=M-1&&heap[child+1]<heap[child])
            child++;
        if(temp>heap[child])
        {
            heap[i]=heap[child];
            heap[child]=temp;
        }
        else
            break;
    }
    heap[i]=temp;
}

void perculateup(int heap[], int i)
{
    int temp=heap[i];
    while(i>0 && temp<heap[(i-1)/2])
    {
        heap[i]=heap[(i-1)/2];
        heap[(i-1)/2]=temp;
        i=(i-1)/2;
    }
}


void insert(int heap[],int M,int x)
{
    heap[M-1]=x;
    perculateup(heap,M-1);
}

int deletemin(int heap[], int M)
{
    int min=heap[0];
    heap[0]=heap[M-1];
    M--;
    perculatedown(heap,0,M);
    return min;
}

int main()
{
    int N,M;
    scanf("%d %d",&N,&M);
    int i,run=1;
    int a[N],b[N][2];
    for(i=0;i<N;i++)
    {
        scanf("%d",&a[i]);
    }
    for(i=0;i<50001;i++){heap[i]=INTMAX;}
    int heapsize=M;
    int temp[M];
    for(i=0;i<M;i++)temp[i]=INTMAX;

    int pb=0,p=0,j=0;
    for(j=0;j<M;j++){insert(heap,j+1,a[j]);}
    for(i=M;i<N;i++)
    {
        b[pb][1]=run;
        b[pb][0]=deletemin(heap,heapsize);
        if(a[i]<b[pb][0])
        {
            temp[p]=a[i];
            p++;
            heapsize--;
            if(heapsize==0)
            {
                heapsize=M;
                for(j=0;j<M;j++){heap[j]=INTMAX;}
                for(j=0;j<p;j++){insert(heap,j+1,temp[j]);}
                for(j=0;j<M;j++){temp[j]=INTMAX;}
                run++;p=0;
            }
        }
        else{
            insert(heap,heapsize,a[i]);
        }
        pb++;
    }
    while(heapsize!=0){
        b[pb][1]=run;
        b[pb][0]=deletemin(heap,heapsize);
        heapsize--;
        pb++;
    }
    run++;
    for(i=0;i<M;i++)
    {
        if(temp[i]==INTMAX){break;}
        heapsize++;
        insert(heap,heapsize,temp[i]);
    }
    while(pb<N){
        b[pb][1]=run;
        b[pb][0]=deletemin(heap,heapsize);
        heapsize--;
        pb++;
    }

    int cnt=1;
    int countspace=0;
    while(cnt<=run)
    {
        for(i=0;i<N;i++)
        {
            if(b[i][1]==cnt)
            {
                if(countspace!=0){printf(" ");}
                printf("%d",b[i][0]);countspace++;
            }
        }
        if(cnt!=run){printf("\n");}
        cnt++;countspace=0;
    }
}