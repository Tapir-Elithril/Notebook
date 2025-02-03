<br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/>
<div align=center>
    <font size=6 face=Times>
A+B with Binary Search Trees
    </font>
    <font size=5 face=楷体>
<br/>
杨亿酬 3230105697
2024-3-27
    </font>
</div>
<div STYLE="page-break-after: always;"></div>

## Chapter 1 Introduction

Binary search tree(BST) is a tree which has the following properties:
1.Binary search tree is a binary tree
2.The left subtree contains nodes whose element is smaller than that of the node
3.The right subtree contains nodes whose element is equal to or bigger than that of the node

Our task is to find an integer *N* by taking advantage of the properties of BST above.The main target is to see whether *N* can be written as A+B where A is an element in Tree1 and B is an element in Tree2.
We input two trees,T1 and T2 and an integer *N* which to be found.
If *N* can be written as A+B,where A is an element in T1 and B is an element in T2,then we print true and all the equations *N = A + B*,else we simply print false.
After that,we print the preorder traversal of *T1* and *T2*.
<div STYLE="page-break-after: always;"></div>

## Chapter 2 Algorithm Specification
- BuildTree
First find the node whose parent_index is -1,defining it as the head of the tree.
Then find the nodes whose parent_index points to the head of the tree,defining them as the left child or the right child of the head.
After that,defining them as the head of the left subtree or the right subtree and repeat the operations above using recursive method.
The following is the pseudo code of the function BuildTree and Build_subtree:
```
function Build_subtree(parent_index, n, a):
    if parent_index == -1:
        return NULL

    Node = create_new_node(a[parent_index][0])
    Node.Left = NULL
    Node.Right = NULL
    
    left_child_index = -1
    right_child_index = -1
    
    for i in range(n):
        if a[i][1] == parent_index:
            if a[i][0] < Node.Element:
                left_child_index = i
            else:
                right_child_index = i
    
    Node.Left = Build_subtree(left_child_index, n, a)
    Node.Right = Build_subtree(right_child_index, n, a)
    
    return Node

function BuildTree(n, a):
    root_index = -1
    
    for i in range(n):
        if a[i][1] == -1:
            root_index = i
            break
    
    return Build_subtree(root_index, n, a)
```
- FindNumber
First find the maximum number and the minimum number of T2,then use function Findbyinorder to find *N*.
In function Findbyinorder,to avoid unnecessary recursions we can simply return if *N-T1->Element > maxT2||N-T1->Element < minT2*,because it is impossible to find an equation under such circumstances.
if *N-T1->Element<=maxT2&&N-T1->Element>=minT2* then first inorder traverse *T1* and for each node of *T1*,use the function Compare to find equations.
In function Compare,we judge whether *X+T->Element* is larger,equal to or smaller than *N*,and use recursive method to attempt to find the proper element in *T2* such that *X+T2->Element == N*.During this process,we take advantage of the property of THE binary search tree that the worst time complexity is only logN when judging whether a proper element is exist for a certain *X* such that *X+T->Element == N*.
The following is the pseudo code of the function FindNumber,Findbyinorder and Compare:
```
function Compare(N, X, T):
    if T != null:
        if X + T.Element == N:
            mark ← mark + 1
            if mark == 1:
                print("true")
            print(N, " = ", X, " + ", T.Element)
        else if X + T.Element < N:
            Compare(N, X, T.Right)
        else:
            Compare(N, X, T.Left)

function Findbyinorder(T1, T2, N, maxT2, minT2):
    if T1 != null:
        if T1.Left != null and T1.Left.Element == T1.Element:
            T1 ← T1.Left
        Findbyinorder(T1.Left, T2, N, maxT2, minT2)
        if N - T1.Element <=> maxT2 and N - T1.Element >= minT2:
            Compare(N, T1.Element, T2)
        if T1.Right != null and T1.Right.Element == T1.Element:
            T1 ← T1.Right
        Findbyinorder(T1.Right, T2, N, maxT2, minT2)

function FindNumber(N, T1, T2):
    maxT2 ← Findmax(T2)
    minT2 ← Findmin(T2)
    Findbyinorder(T1, T2, N, maxT2, minT2)
    if mark == 0:
        print("false")
```
- Preorder
    print the elements of T1 and T2 in preorder
```
function Preorder(T,n)
    if T != NULL then
        if cnt != n then
            print(T.Element, " ")
            cnt ← cnt + 1
            Preorder(T.Left, n)
            Preorder(T.Right, n)
        else
            print(T.Element)
```

Data structure analysis:
- 2D array
  
Two 2D arrays each have n1 and n2 rows and both have two columns are used for building the Tree *T1* and *T2*,where the first column is used for storing the elements of the nodes and the second column is used for storing the head_index which points to the parent of the node.
  
- Binary search tree(BST):the main data structure of the programme
  
The definition of a binary search tree:
1.Every node has an element which is an integer, and the elements are distinct.
2.The elements in a nonempty left subtree must be smaller than the element in the root of the subtree.
3.The elements in a nonempty right subtree must be larger than the element in the root of the subtree.
4.The left and right subtrees are also binary search trees.
Note that the binary search tree we use in the programme is a bit different from the definition above,because in the programme,nodes having the same element is allowed(if two nodes share the same element,then one node is the right child of the other,if more nodes share the same element,then each one is the right child of another)
The advantage of a binary search tree is that it can quickly perform search(the main task of the programme), insertion, and deletion operations, with a time complexity of O(logN), where N is the number of nodes in the tree.
 <div STYLE="page-break-after: always;"></div>

## Chapter 3 Testing Results
  <table>
  	<tr>
  		<th></th>
  		<th>input</th>
          <th>output</th>
          <th>corresponding purpose</th>
  	</tr>
  	<tr>
  		<th>1</th>
  		<th>
        8<br/>
12 2<br/>
16 5<br/>
13 4<br/>
18 5<br/>
15 -1<br/>
17 4<br/>
14 2<br/>
18 3<br/>
7<br/>
20 -1<br/>
16 0<br/>
25 0<br/>
13 1<br/>
18 1<br/>
21 2<br/>
28 2<br/>
36</th>
          <th>true<br/>
36 = 15 + 21<br/>
36 = 16 + 20<br/>
36 = 18 + 18<br/>
15 13 12 14 17 16 18 18<br/>
20 16 13 18 25 21 28</th>
          <th>comprehensive sample when the result is true</th>
  	</tr>
  	<tr>
  		<th>2</th>
  		<th>5<br/>
10 -1<br/>
5 0<br/>
15 0<br/>
2 1<br/>
7 1<br/>
3<br/>
15 -1<br/>
10 0<br/>
20 0<br/>
40</th>
          <th>false<br/>
10 5 2 7 15<br/>
15 10 20</th>
          <th>comprehensive sample when the result is false</th>
  	</tr>
      	<tr>
  		<th>3</th>
  		<th>4<br/>
0 -1<br/>
-2000000000 0<br/>
1000000000 0<br/>
2000000000 2<br/>
3<br/>
-1000000000 -1<br/>
-2000000000 0<br/>
0 0<br/>
0</th>
          <th>true<br/>
0 = 0 + 0<br/>
0 = 1000000000 + -1000000000<br/>
0 = 2000000000 + -2000000000<br/>
0 -2000000000 1000000000 2000000000<br/><br/>
-1000000000 -2000000000 0</th>
          <th>testing whether the programme can execute if the value k is very large</th>
  	</tr>
      	<tr>
  		<th>4</th>
  		<th>7<br/>
18 -1<br/>
17 0<br/>
17 1<br/>
18 0 <br/>
18 2<br/>
18 3 <br/>
18 4<br/>
5<br/>
17 -1<br/>
16 0<br/>
16 1<br/>
17 0<br/>
17 3<br/>
34</th>
          <th>true<br/>
34 = 17 + 17<br/>
34 = 18 + 16<br/>
18 17 17 18 18 18 18<br/>
17 16 16 17 17</th>
          <th>testing the condition that many nodes share the same element</th>
  	</tr>
      	<tr>
  		<th>5</th>
  		<th>1<br/>
20 -1<br/>
1<br/>
15 -1<br/>
30<br/></th>
          <th>false<br/>
20<br/>
15</th>
          <th>testing the trees with only the head node</th>
  	</tr>
      	<tr>
  		<th>6</th>
  		<th>see in 6.txt</th>
          <th>see in 6.answer.txt</th>
          <th>testing the condition that n1,n2 is very large</th>
  	</tr>
  </table>
<br/>


<div STYLE="page-break-after: always;"></div>

## Chapter 4: Analysis and Comments 
- Time complexity:

The worst time complexity of the functions is as follows:
BuildTree:O(N<sup>2</sup>)
The function first iterates through the array *a* (of size N) to find the root index. This takes O(N) time. Then it calls Build_subtree.The function Build_subtree recursively builds the left and right subtrees of the tree. For each node, it iterates through the entire array *a* (of size N) to find the left and right child indices. Therefore, the time complexity is O(N<sup>2</sup>). The overall time complexity is O(N<sup>2</sup>).

FindNumber:O(NlogN)
Function Findmax and Findmin share the time complexity of both O(logN)
Function Findbyinorder uses the inorder traversal method to traverse *T1*;therefore,the time complexity of this function is O(N*the time complexity of function Compare)
Function Compare compares *N-T1->Element* with the elements in *T2* by taking advantage of the properties of binary search tree,whose worst time complexity is O(logN)
Therefore,the total time complexity of the function FindNumber is O(NlogN)
Note that when the tree degenerates to a linked list,the time complexity is O(N) correspondingly

Preorder:O(N)
The function performs a preorder traversal of the tree. For each node, it prints the element and recursively visits its left and right children. Since each node is visited once, the time complexity is O(N).

Total time complexity of the programme is O(N<sup>2</sup>)

- Space complexity:

The worst space complexity of the functions is as follows:
BuildTree:O(N)
The recursive calls create a new stack frame for each node. Since the maximum depth of the recursion is the height of the tree (which can be at most N for a skewed tree), the space complexity is O(N).

FindNumber:O(NlogN)
Function Findmax and Findmin share the space complexity of both O(logN)
Function Findbyinorder uses the inorder traversal method to traverse *T1*;therefore,the space complexity of this function is O(N*the space complexity of function Compare)
unction Compare compares *N-T1->Element* with the elements in *T2* by taking advantage of the properties of binary search tree,whose worst space complexity is O(logN)
Therefore,the total time complexity of the function FindNumber is O(NlogN)

Preorder:O(N)
Each call of the function prints one element of the tree,since the tree has n nodes,the total time complexity of the function if O(N).

Total space complexity of the programme is O(NlogN)


Through the project,we could more detailedly understand the advantages of the binary search tree.
​    Hope the project can give us a rough but more intuitive understanding of the binary search tree.


### Declaration 
I hereby declare that all the work done in this project titled "A+B with Binary Search Trees" is of my independent effort.