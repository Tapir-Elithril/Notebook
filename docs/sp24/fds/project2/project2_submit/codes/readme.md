The programme is used for finding whether an integer N can be written as A+B whether A is an element in Tree T1 and B is an element in Tree T2.
The programme takes advantage of the characteristic of binary search tree(BST) where the left subtree of nodes contains only nodes smaller than the node's element while the right subtree of nodes contains only nodes equal to or bigger than the node's element.

​	The whole programme is run under gcc.exe version 13.1.0

In windows powershell
1.executing the following command to compile

```
gcc ./main.c -o ./main.exe
```

2.executing the following command to run the programme 

```
./main.exe
```

3.Inputs:
a number n1:the number of nodes in T1
an 2D array a[][2] where the first column is the element and the second column is the parent_index used for constructing the relation between the children and the parent
a number n2:the number of nodes in T2
an 2D array b[][2](similar to a[][2])
a number N which is to be found 

Outputs:
if N can be written as A+B,where A is in T1 and B is in T2
print true
some equations:N = A + B
    note that the same equation only appears once
then print the preorder traversal of T1 and the preorder traversal of T2

if N cannot be written as A+B
simply print false
then print the preorder traversal of T1 and the preorder traversal of T2

the programme requires that all the elements involved in the project is in the range of -20000000000 - 2000000000
both the tree T1 and T2 are not an empty tree

4.the output can be seen in result.txt

if you want to test the given inputs(written in 1-6.txt),after compiling,executing
```
Get-Content .\@.txt |./main
```
replace @ with 1-6 for the input you want to test 

e.g. if you want to test the input in 4.txt,then executing
```
Get-Content .\4.txt |./main
```