#include<stdio.h>
#include<stdlib.h>
#define MaxVertexNum 1001
#define MaxEdgeNum 20
#define MaxWeight 101
// Macro definition to limit the space of data structure types

typedef enum {false, true} bool;
// bool type, used to determine if a sequence is a Dijkstra sequence

typedef struct AdjVNode *PtrToAdjVNode; 
struct AdjVNode{
    int AdjV;
    int Weight;
    PtrToAdjVNode Next;
};
// Unidirectional edge, contains the node number AdjV that the edge points to, the weight of the edge Weight, a pointer Next to the next edge, and a pointer Reverse to the reverse edge

typedef struct Vnode{
    PtrToAdjVNode FirstEdge;
} AdjList[MaxVertexNum];
// Node, contains a pointer FirstEdge to the first edge starting from this node

typedef struct GNode *PtrToGNode;
struct GNode{  
    int Nv;
    int Ne;
    AdjList G;
};
typedef PtrToGNode LGraph;
// Graph, contains the number of nodes, the number of edges, and the adjacency list G of the graph
// G is an array of type AdjList, each element is a structure of Vnode, which stores all the vertex and edge information of the graph

bool IsDijkSeq(LGraph G, int Seq[])//Seq[G->Nv]
{
    int i,j;
    int weight[G->Nv+1];// Used to store the distance from the remaining vertices to the existing graph
    weight[0]=-1;// Not used
    for(i=1;i<G->Nv+1;i++){weight[i]=MaxWeight;}// Initially set to Maxweight to indicate no connection
    // Store the distance from each vertex to the existing graph in weight
        // Core part of Dijkstra Algorithm, application of greedy algorithm
    PtrToAdjVNode TempEdge=(PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    TempEdge=G->G[Seq[0]].FirstEdge;
    weight[Seq[0]]=MaxWeight+1;// Indicates that it has been visited
    while(TempEdge!=NULL)
    {
        weight[TempEdge->AdjV]=TempEdge->Weight;
        TempEdge=TempEdge->Next;
    }
    // Traverse TempEdge to modify the weight of the vertices adjacent to the existing graph
    for(i=1;i<G->Nv-1;i++)
    {
        int temp=0;// Record whether the next edge is connected to the existing graph, if connected, record the distance
        TempEdge=G->G[Seq[0]].FirstEdge;
        while(TempEdge!=NULL)
        {
            if(TempEdge->AdjV==Seq[i]){temp=TempEdge->Weight;break;}
            TempEdge=TempEdge->Next;
        }
        // Traverse TempEdge to record the distance from the existing graph to the next vertex (if connected)
        int min=MaxWeight;
        for(j=1;j<G->Nv+1;j++)
        {
            if(weight[j]<min){min=weight[j];}
        }
        // Record the minimum distance from the existing graph to the adjacent vertices
        if(temp!=min){return false;}
        // If the minimum distance from the existing graph to the adjacent vertices is not equal to the distance from the existing graph to the next vertex, it is not a dijkstra sequence
        // If the minimum distance from the existing graph to the adjacent vertices is equal to the distance from the existing graph to the next vertex, include this vertex in the existing graph
        // The specific operation is: traverse the vertices adjacent to the existing graph and the vertices adjacent to this vertex
        else{
            weight[Seq[i]]=MaxWeight+1;// Indicates that it has been visited
            PtrToAdjVNode TempEdge2=(PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
            TempEdge2=G->G[Seq[i]].FirstEdge;
            while(TempEdge2!=NULL)
            {
                PtrToAdjVNode TempEdge1=(PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
                TempEdge1=G->G[Seq[0]].FirstEdge;
                if(weight[TempEdge2->AdjV]==MaxWeight+1){TempEdge2=TempEdge2->Next;}
                // If the vertex pointed to by the edge has been visited, directly point to the next vertex
                if(TempEdge2==NULL){break;}
                int cnt=0;
                while(TempEdge1!=NULL)
                {
                    if(TempEdge1->AdjV==TempEdge2->AdjV){cnt=1;break;}
                    TempEdge1=TempEdge1->Next;
                }
                if(cnt==1){
                    // If there is an edge connected to this vertex and not connected to the existing graph
                    // Judge its distance to the graph and its distance to the existing distance + the distance from the vertex to it
                    // Set the distance of the edge to the smaller distance
                    if(temp+TempEdge2->Weight<TempEdge1->Weight)
                    {TempEdge1->Weight=temp+TempEdge2->Weight;}
                }
                else{
                    // If there is an edge connected to this vertex but not connected to the existing graph
                    // Create a new edge to connect the existing graph to the vertex connected to this vertex 
                    PtrToAdjVNode NewEdge=(PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
                    NewEdge->AdjV=TempEdge2->AdjV;
                    // Set weight to the existing distance + the distance from the vertex to it
                    NewEdge->Weight=temp+TempEdge2->Weight;
                    NewEdge->Next=G->G[Seq[0]].FirstEdge;
                    G->G[Seq[0]].FirstEdge=NewEdge;
                }
                TempEdge2=TempEdge2->Next;
            }
            PtrToAdjVNode TempEdge1_=(PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
            TempEdge1_=G->G[Seq[0]].FirstEdge;
            while(TempEdge1_!=NULL)
            {
                // Traverse TempEdge1 to modify the weight of the vertices adjacent to the existing graph
                if(weight[TempEdge1_->AdjV]<=MaxWeight){weight[TempEdge1_->AdjV]=TempEdge1_->Weight;}
                TempEdge1_=TempEdge1_->Next;
            }
        }
    }
    return true;
}

int main()
{
    //BuildGraph
    int Nv,Ne;// Number of Vertices and Number of Edges
    scanf("%d %d",&Nv,&Ne);
    LGraph G=(LGraph)malloc(1000000*sizeof(struct AdjVNode));
    // Apply for enough space to avoid bloody lessons
    G->Nv=Nv;G->Ne=Ne;
    int i,j;
    for(i=0;i<Nv;i++)
    {
        G->G[i].FirstEdge=NULL;
        // Initialize each vertex's FirstEdge pointer to NULL
    }
    int v1,v2,weight;
    for(i=0;i<Ne;i++)
    {
        scanf("%d %d %d",&v1,&v2,&weight);
        PtrToAdjVNode NewEdge=(PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
        // Create a unidirectional edge connecting v1 and v2 with weight
        NewEdge->AdjV=v2;
        NewEdge->Weight=weight;
        NewEdge->Next=G->G[v1].FirstEdge;
        // The Next pointer of NewEdge points to the first edge of the current vertex v1. If the current vertex v1 has no edge, then G->G[v1].FirstEdge will be NULL
        G->G[v1].FirstEdge=NewEdge;
        // Update the first edge of vertex v1 to NewEdge. NewEdge becomes the first edge of the edge list starting from vertex v1
        PtrToAdjVNode ReverseEdge=(PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
        ReverseEdge->AdjV=v1;
        ReverseEdge->Weight=weight;
        ReverseEdge->Next=G->G[v2].FirstEdge;
        G->G[v2].FirstEdge=ReverseEdge;
        // Add reverse edges to form a bidirectional graph
    }

    //Dijkstra Algorithm
    int K;
    scanf("%d",&K);
    int ans[K];// Store results
    for(i=0;i<K;i++)
    {
        int Seq[Nv];
        // The sequence to be judged
        for(j=0;j<Nv;j++)
        {
            scanf("%d",&Seq[j]);
        }
        // Judge whether Seq[G->Nv] is a Dijkstra Sequence. If it is, output yes, otherwise output no
        if(IsDijkSeq(G, Seq)==true){ans[i]=1;}
        // Call the function IsDijkSeq to judge whether it is a Dijkstra Sequence
        else{ans[i]=0;}
    }
    for(i=0;i<K;i++)
    {
        // Output according to the result data of ans
        if(ans[i]==1){printf("Yes\n");}
        else{printf("No\n");}
    }
    return 0;
}
