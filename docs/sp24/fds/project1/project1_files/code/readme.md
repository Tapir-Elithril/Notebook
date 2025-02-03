	The programme is used for comparing the time complexity of 4 searching methods,
namely iterative_sequential,recursive_sequential,iterative_binary and recursive_binary.
The target is to find N in a list of numbers ranging from 0 to N-1 and print out the worst time spent of each searching method.
By including <time.h>,the programme is able to record the time spent running the functions
and by repeating the functions K times,the duration can be large enough to lower the margin of error.
The total time spent of running each function K times is recorded in the table in the report. 

​	The whole programme is run under gcc.exe version 13.1.0

Run the programme by
1.executing command 

```
gcc ./main.c -o ./main.exe
```
2.executing command 

```
./main.exe
```

3.Inputs:N,the function number to be tested j(where j=0 represents iterative version of sequential search,j=1 represents recursive version of sequential search,j=2 represents iterative version of binary search and j=3 represents recursive version of binary search) and the minimum time of duration mintime(required to be larger than 10 and for more accurate outputs,larger than 1000 when testing binary search) 

 Outputs:K and duration

sample input：
100 3 1000
sample output:
14308728 1.001000

sample input：
1000 1 10
sample output:
2731 0.011000
