#ifndef TREE_H
#define TREE_H
#endif
/*define tree.h for use in main.c*/

static int mark=0;
/*used for recording whether N can be found in the function findbyinorder*/
static int cnt=1;
/*used for delete the space at the end of the output of the preorder traversal of T1*/
static int dele=0;
/*used for deleting repeated equations*/
typedef int ElementType;

typedef struct TreeNode *Tree;
struct TreeNode {
    ElementType Element;
    Tree  Left;
    Tree  Right;
};
/*initialize the struct of Tree
Tree consists of nodes containing a pointer to the element and pointers to the left and to the right*/

Tree Build_subtree(int parent_index, int n, int a[][2]) 
{
    /*build the left subtree and the right subtree of Tree T through recursive method*/
    if(parent_index==-1)
    {
        return NULL;
    }
    /*if index==-1 then do nothing*/
    Tree Node=(Tree)malloc(sizeof(struct TreeNode));
    Node->Element=a[parent_index][0];
    Node->Left=NULL;
    Node->Right=NULL;
    /*create a parent node*/

    int left_child_index=-1;
    int right_child_index=-1;
    /*initialize the left and right child index */

    for(int i=0;i<n;i++)
    {
        if(a[i][1]==parent_index)
        {
            if(a[i][0]<Node->Element){left_child_index=i;}
            else{right_child_index=i;}
        }
    }
    /*use parent_index to find left child or right child*/

    Node->Left=Build_subtree(left_child_index, n, a);
    /*use recursive method to find the child of the left child*/
    Node->Right=Build_subtree(right_child_index, n, a);
    /*use recursive method to find the child of the right child*/

    return Node;
}

Tree BuildTree(int n, int a[][2])
{
    /*build a tree containing n nodes using a 2D array a[][2]*/
    int root_index=-1;/*define root_index*/
    
    for(int i=0;i<n;i++)
    {
        if(a[i][1]==-1)
        {
            root_index=i;
            break;
        }
    }
    /*find the head of the tree T*/
    return Build_subtree(root_index,n,a);
    /*build the tree T through recursive method*/
}

void Preorder(Tree T,int n)/*n is used for deleting the space at the end of the output*/
{
    if(T!=NULL)
    {
        if(cnt!=n)/*count whether we are going to print the last element of T1*/
        {
            printf("%d ",T->Element);cnt++;
            Preorder(T->Left,n);
            Preorder(T->Right,n);
            /*print the element of T and a space after the element
            unless it is the last node of T1*/
        }
        else{printf("%d\n",T->Element);}
        /*when printing the last element of T1,printf the element and \n instead*/
    }
    return ;
}

int Findmax(Tree T)
{
    while(T->Right!=NULL){T=T->Right;}
    return T->Element;
}
/*find the max element of tree T by visit the element of the rightmost node*/

int Findmin(Tree T)
{
    while(T->Left!=NULL){T=T->Left;}
    return T->Element;
}
/*find the min element of tree T by visit the element of the leftmost node*/

void Compare(int N,int X,Tree T)
{
    if(T!=NULL)
    {
        if(X+T->Element==N)
        {
           mark++;
           /*if the first equation is found print true */
           if(mark==1){printf("true\n");}
           printf("%d = %d + %d\n",N,X,T->Element);
        }
        else if(X+T->Element<N)
        {
            Compare(N,X,T->Right);
            /*if X+T->Element is not large enough,enlarge T->Element by using the characteristic of BST*/
        }
        else
        {
            Compare(N,X,T->Left);
            /*if X+T->Element is too large,lessen T->Element by using the characteristic of BST*/
        }
    }
    return ;
}
/*worst time complexity logN(the level of BST)*/

void Findbyinorder(Tree T1,Tree T2,int N,int maxT2,int minT2,int del)
{
    if(T1!=NULL)
    {
        while(T1->Left!=NULL&&T1->Left->Element==T1->Element){T1=T1->Left;}
        /*ensure the same equation only appears once when traversing T1*/
        Findbyinorder(T1->Left,T2,N,maxT2,minT2,del);
        /*if N-T1->Element>maxT2||N-T1->Element<minT2 then there's no need for recursives
        simply return; */
        if(N-T1->Element<=maxT2&&N-T1->Element>=minT2)
        {
            if(T1->Element!=del||dele==0)
            {
                Compare(N,T1->Element,T2);
                if(T1->Element==del){dele++;}
            }
            /*first inorder traverse T1,then compare T1 with the elements of T2*/
            /*use del and dele to delete repeat equation if the head node of T1 shares the same element with
            at least one child of it and the element can form N with an element in T2*/
        }
        while(T1->Right!=NULL&&T1->Right->Element==T1->Element){T1=T1->Right;}
        /*ensure the same equation only appears once*/
        Findbyinorder(T1->Right,T2,N,maxT2,minT2,del);
        /*inorder traversal of T1*/
        /*ensure the equations are output in ascending order of the values of A*/
    }
    return ;
}
/*worst time complexity N(inorder traversal of T1)*/

void FindNumber(int N,Tree T1,Tree T2,int del)
{
        int maxT2=Findmax(T2);
        int minT2=Findmin(T2);
        /*used for deserting unnecessary recursions*/
        Findbyinorder(T1,T2,N,maxT2,minT2,del);
    if(mark==0){printf("false\n");}
    /*if no equation is found,we should simply print false */
    return ;
}
/*total worst time complexity NlogN*/
