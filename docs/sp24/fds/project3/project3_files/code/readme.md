The programme is used for checking whether a sequence for a graph is a dijkstra sequence or not,if it is,print yes,while no otherwise.

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
two positive integers,Nv(≤10<sup>3</sup>)(the vertices are numbered from 1 to N ),Ne(≤10<sup>5</sup>),followed by Ne lines.
Each line describes an edge by giving the two vertices linked by the edge and an positive integer weight(≤100).
Then an integer K(≤100),followed by K lines of sequences,each is a permutation of the Nv vertices.

Outputs:
for each of the K sequence,print yes if it is a dijkstra sequence,while no otherwise.

the programme requires that the graph is undirected and connected 


if you want to test the given inputs(written in 1-5.txt),after compiling,executing
```
Get-Content .\@.txt |./main
```
replace @ with 1-5 for the input you want to test 

e.g. if you want to test the input in 4.txt,then executing
```
Get-Content .\4.txt |./main
```