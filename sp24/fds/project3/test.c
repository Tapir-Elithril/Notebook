#include<stdio.h>
#define INTMAX 20
int main()
{
    int his[20];//linkedlisthistory    linkedlist-type-array
    int cache[20];
    int pageID[20];//pageID[0] is not useful
    int HTh[20][20];
    //int HTc[20][20]; 
    int K,N,M;
    scanf("%d %d %d",&K,&N,&M);
    int i;
    for(i=0;i<20;i++)
    {
        cache[i]=0;
    }
    for(i=0;i<20;i++)
    {
        pageID[i]=0;
    }
    int j;
    for(i=0;i<20;i++)
    {
        for(j=0;j<20;j++)
        {HTh[i][j]=-1;/*HTc[i][j]=-1;*/}//HT[pageID][index]
    }
    int hthindex[20];
    for(j=0;j<20;j++){hthindex[j]=0;}
    for(i=0;i<M;i++)
    {
        scanf("%d",&his[i]);
        HTh[his[i]][hthindex[his[i]]]=i;
        hthindex[his[i]]++;
    }
    int his_rear=0,his_front=0,his_size=0;
    int cache_rear=0,cache_front=0,cache_size=0;

    for( ;his_front!=M;his_front++)
    {
        pageID[his[his_front]]++;
        if(pageID[his[his_front]]>=2&&pageID[his[his_front]]<K)
        {
            int cnt=0;
            /*for(i=his_rear;i<his_front;i++)
            {
                if(his[i]==his[his_front])
                {
                    his[i]=0;cnt++;
                    if(cnt==pageID[his[his_front]]-1){break;}
                }
            }*/
            int index=0;
            while(HTh[his[his_front]][index]!=-1)
            {
                if(HTh[his[his_front]][index]!=-2&&HTh[his[his_front]][index]<his_front&&HTh[his[his_front]][index]>=his_rear)
                {his[HTh[his[his_front]][index]]=0;cnt++;HTh[his[his_front]][index]=-2;}
                index++;
            }
        }

        else if(pageID[his[his_front]]>=K)
        {
            cache[cache_front]=his[his_front];
            int cnt=0;
            for(i=his_rear;i<his_front&&pageID[his[his_front]]==K;i++)
            {
                if(his[i]==his[his_front])
                {
                    his[i]=0;cnt++;
                    if(cnt==K-1){break;}
                }
            }
            his_size-=cnt;
            his[his_front]=0;

            int mark=0;
            for(i=cache_rear;i<cache_front;i++)
            {
                if(cache[i]==cache[cache_front])
                {
                    cache[i]=INTMAX;mark++;break;
                }
            }
            if(mark==0)
            {
                if(cache_size==N)
                {
                    pageID[cache[cache_rear]]=0;
                    cache_rear++;
                }
                else{cache_size++;}
            }
            cache_front++;
        }
        else
        {
            if(his_size==N)
            {
                pageID[his[his_rear]]=0;
                his_rear++;
            }
            else{his_size++;}
        }
        while(cache[cache_rear]==INTMAX){cache_rear++;}
        while(his[his_rear]==0){his_rear++;}
    }

    int hiscnt=0;
    if(his_size==0){printf("-\n");}
    else
    {
            for(i=his_rear;i<his_front;i++)
        {
            if(his[i]!=0)
            {
                hiscnt++;
                if(hiscnt<his_size)
                {
                    printf("%d ",his[i]);
                }
                else{printf("%d\n",his[i]);break;}
            }
        }
    }
    int cachecnt=0;
    if(cache_size==0){printf("-");}
    else
    {    
            for(i=cache_rear;i<cache_front;i++)
        {
            if(cache[i]!=INTMAX)
            {
                cachecnt++;
                if(cachecnt<cache_size)
                {
                    printf("%d ",cache[i]);
                }
                else{printf("%d",cache[i]);break;}
            }
        }
    }
}