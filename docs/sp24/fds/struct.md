# 常用结构体
## 链表
```C
typedef struct Node *PtrToNode;//将struct Node*类型定义为PtrToNode,表示指向Node的一个指针
struct Node {
    int key; 
    PtrToNode next; 
};//每个Node中包含一个键值key和一个指向下一个Node的指针next
typedef PtrToNode list;//将PtrToNode类型定义为list,表示list也是一个指向Node的指针
```
```C
typedef struct Node {
    int key;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct {
    Node *head;
    Node *tail;
} List;//定义一个结构，包含两个指向Node的指针
```
## 树
```C
typedef struct TreeNode *PtrTreeNode;
typedef struct TreeNode {
    int key;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;
typedef PtrTreeNode BST;//BST类型是一个指向树根节点的指针
```
## 堆
```C
typedef struct {
    int data[MAX_SIZE];  
    int size;  
} Heap;
```
```C
typedef struct TreeNode {
    int key;            
    struct TreeNode *left; 
    struct TreeNode *right;
} TreeNode;
typedef struct {
    TreeNode* root; 
} Heap;
```
## 图
```C
typedef struct AdjVNode *PtrToAdjVNode; 
struct AdjVNode{
    int AdjV;//指向节点编号
    int Weight;
    PtrToAdjVNode Next;//指向下一条边
};//边

typedef struct Vnode{
    PtrToAdjVNode FirstEdge;//指向第一条边
} AdjList[MaxVertexNum];//节点

typedef struct GNode *PtrToGNode;
struct GNode{  
    int Nv;//节点数
    int Ne;//边数
    AdjList G;//节点结构数组，存储每个节点第一条边的指针
    //通过Graph->G[Seq[N]].FirstEdge访问
};//图
typedef PtrToGNode LGraph;
```
