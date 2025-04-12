This program is based on student1.  
Each record consists of a name (w/o space) and scores are in integer ranging from 1 to 5.  
In addition to the first homework,we are asked to write a CLI which reads scoring records of students and prints out a summary sheet.  
Specifically,the user can input an arbitary number of students each takes arbitary number of courses.  
Each record consists of the course id/name and the score the student gained.  
Note that a student usually won't choose every available course.  
We use NA to represent that a student didn't take the certain course.
  
The program is running under g++ (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0  

Run the program by executing `make run`.  
  
The result will display in the terminal.

sample input:(14 tests)
```text
K.Alice Chinese 4 Math 5 Physics 2 Biology 5 History 3 Politics 4
J.Bob English 5 Chemistry 3 Chinese 3 Math 4 Geography 3 Politics 5 History 4 Physics 3 Biology 3
F.Charlie Biology 3 Politics 3 Chinese 5 Math 4 Chemistry 2
M.David Geography 4
P.Eva Politics 4 English 4 Math 2 Chinese 3 History 4 Biology 5
S.Frank English 2 Math 4 Chinese 5
G.Grace History 5 Geography 4 Politics 3 Chinese 4 Math 1 Biology 4
V.Helen Physics 3 Math 4 English 4 Politics 3 Geography 2 Chinese 5 Chemistry 3 Biology 1
L.Ivy Chinese 4 Math 3 English 4 Physics 4 Chemistry 2 Biology 3
N.Jack Chinese 3 Math 5 English 2 History 4 Politics 2 Geography 5
I.Kate Math 4 Physics 2 Chemistry 3 Biology 5
H.Leo English 3 Chinese 5 Politics 2 Geopgraphy 4 History 5
T.Mia English 5 History 5 Geography 5 Physics 4 Math 5
W.Noah Politics 2 Geography 1 Math 1 Chinese 2 Biology 1 History 1
StudentA ads 93 oop 91 fds 79
StudentB cg 87 bs 92 os 88
<Ctrl + D>
```

sample output:
```text
no        name      Chinese   Math      English   Physics   Chemistry Biology   History   Politics  Geography average   
1         K.Alice   4         5         NA        2         NA        5         3         4         NA        3.83333   
2         J.Bob     3         4         5         3         3         3         4         5         3         3.66667   
3         F.Charlie 5         4         NA        NA        2         3         NA        3         NA        3.4       
4         M.David   NA        NA        NA        NA        NA        NA        NA        NA        4         4         
5         P.Eva     3         2         4         NA        NA        5         4         4         NA        3.66667   
6         S.Frank   5         4         2         NA        NA        NA        NA        NA        NA        3.66667   
7         G.Grace   4         1         NA        NA        NA        4         5         3         4         3.5       
8         V.Helen   5         4         4         3         3         1         NA        3         2         3.125     
9         L.Ivy     4         3         4         4         2         3         NA        NA        NA        3.33333   
10        N.Jack    3         5         2         NA        NA        NA        4         2         5         3.5       
11        I.Kate    NA        4         NA        2         3         5         NA        NA        NA        3.5       
12        H.Leo     5         NA        3         NA        NA        NA        5         2         NA        3.8       
13        T.Mia     NA        5         5         4         NA        NA        5         NA        5         4.8       
14        W.Noah    2         1         NA        NA        NA        1         1         2         1         1.33333   
          average   3.9       3.5       3.6       3.0       2.6       3.3       3.9       3.1       3.4       
          min       2         1         2         2         2         1         1         2         1         
          max       5         5         5         4         3         5         5         5         5         
```