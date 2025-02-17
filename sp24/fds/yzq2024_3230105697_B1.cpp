/* Author: Yang YiChou;  ID: 3230105697;  No.01 */
#include<stdio.h>
#define INTMAX 20001
int main()
{
    int his[100001];//linkedlisthistory    linkedlist-type-array
    int cache[100001];
    int pageID[20001];//pageID[0] is not useful
    
    int hashhis[20001];
    int hashcache[20001];
    
    int K,N,M;
    scanf("%d %d %d",&K,&N,&M);
    int i;
    for(i=0;i<100001;i++)
    {
        cache[i]=0;
    }
    for(i=0;i<20001;i++)
    {
        pageID[i]=0;
        hashhis[i]=-1;
        hashcache[i]=-1;
    }
    for(i=0;i<M;i++)
    {
        scanf("%d",&his[i]);
    }
    int his_rear=0,his_front=0,his_size=0;
    int cache_rear=0,cache_front=0,cache_size=0;

    for( ;his_front!=M;his_front++)
    {
        pageID[his[his_front]]++;
        if(pageID[his[his_front]]>=2&&pageID[his[his_front]]<K)
        {
            /*int cnt=0;
            for(i=his_rear;i<his_front;i++)
            {
                if(his[i]==his[his_front])
                {
                    his[i]=0;cnt++;
                    if(cnt==pageID[his[his_front]]-1){break;}
                }
            }*/
            if(hashhis[his[his_front]]>=his_rear&&hashhis[his[his_front]]<his_front)
            {
                his[hashhis[his[his_front]]]=0;
                hashhis[his[his_front]]=his_front;
            }
        }

        else if(pageID[his[his_front]]>=K)
        {
            cache[cache_front]=his[his_front];
            /*int cnt=0;
            for(i=his_rear;i<his_front&&pageID[his[his_front]]==K;i++)
            {
                if(his[i]==his[his_front])
                {
                    his[i]=0;cnt++;
                    if(cnt==K-1){break;}
                }
            }*/
            //his_size-=cnt;
            if(pageID[his[his_front]]==K&&hashhis[his[his_front]]>=his_rear&&hashhis[his[his_front]]<his_front)
            {
                his[hashhis[his[his_front]]]=0;
                hashhis[his[his_front]]=-1;
                his_size-=1;
            }
            his[his_front]=0;

            int mark=0;
            /*for(i=cache_rear;i<cache_front;i++)
            {
                if(cache[i]==cache[cache_front])
                {
                    cache[i]=INTMAX;mark++;break;
                }
            }*/
            if(hashcache[cache[cache_front]]>=cache_rear&&hashcache[cache[cache_front]]<cache_front)
            {
                mark=1;
                cache[hashcache[cache[cache_front]]]=INTMAX;
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
            hashcache[cache[cache_front]]=cache_front;
            cache_front++;
        }
        else
        {
            if(his_size==N)
            {
                pageID[his[his_rear]]=0;
                hashhis[his[his_rear]]=-1;
                his_rear++;
                hashhis[his[his_front]]=his_front;
            }
            else{
                his_size++;
                hashhis[his[his_front]]=his_front;
            }
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