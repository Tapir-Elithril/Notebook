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



if you want to test the given inputs(written in 1-5.txt),after compiling,executing
```
Get-Content .\@.txt |./main
```
replace @ with 1-5 for the input you want to test 

e.g. if you want to test the input in 4.txt,then executing
```
Get-Content .\4.txt |./main
```



sample input1：
8
12 2
16 5
13 4
18 5
15 -1
17 4
14 2
18 3
7
20 -1
16 0
25 0
13 1
18 1
21 2
28 2
36
sample output1:
true
36 = 15 + 21
36 = 16 + 20
36 = 18 + 18
15 13 12 14 17 16 18 18
20 16 13 18 25 21 28
//the same as the sample given by pta
sample input2：
5
10 -1
5 0
15 0
2 1
7 1
3
15 -1
10 0
20 0
40
sample output2:
false
10 5 2 7 15
15 10 20
//the same as the sample given by pta
sample input3：
4
0 -1
-2000000000 0
1000000000 0
2000000000 2
3
-1000000000 -1
-2000000000 0
0 0
0
sample output3:
true
0 = 0 + 0
0 = 1000000000 + -1000000000
0 = 2000000000 + -2000000000
0 -2000000000 1000000000 2000000000
-1000000000 -2000000000 0
//used for testing whether the programme can execute if the value k is very large
sample input4:
7
18 -1 
17 0
17 1
18 0 
18 2
18 3 
18 4
5
17 -1
16 0
16 1
17 0
17 3
34
sample output4:
true
34 = 17 + 17
34 = 18 + 16
18 17 17 18 18 18 18
17 16 16 17 17
//used for testing the condition that many nodes share the same element
sample input5:
1
20 -1
1
15 -1
30
sample output5:
false
20
15
//used for testing trees with only the head node 