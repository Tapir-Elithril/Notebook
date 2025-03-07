# 面向对象程序设计  

## Using Objects Week 1 - 2  
### The string class  
```cpp
#include<string>
string str;
string str = "Hello";
cin >> str;
cout << str;
```
```c
char charr1[20];
char charr2[20] = "jaguar";

string str1;
string str2 = "panther";

charr1 = charr2; //illegal(in C,we have to use strcpy)
str1 = str2; //legal
```
```cpp
string str3;
str3 = str1 + str2;
str1 += str2;
str1 += "a string literal";
```
constructors(ctors)  
```cpp
string(const char *cp,int len);
string(const string& s2,int pos);
string(const string& s2,int pos,int len);

substr(int pos,int len);

assign(...);
insert(const string&,int len);
insert(int pos,const string& s);
erase(...);
append(...);
replace(...);
replace(int pos,int len,const string& s);
```
### File I/O  
```cpp
#include <ifstream> //read from file
#include <ofstream> //write to file

ofstream file1("C:\\test.txt");
file1 << "Hello World" << std::endl;
ifstream file2("C:\\test.txt");
std::string str;
file2 >> str;
```
### Memory Model  
```cpp
int i;//global vars
string str;
static int j;//static global vars
f()
{
    int k;//local vars
    static l;//static local vars
    int *p = malloc(sizeof(int));//allocated local vars
}
```

- Global data:global vars,static global vars,static local vars(i,j,l,str)  
- Stack:local vars(k)  
- Heap:dynamically allocated vars(*p)  
  
global vars:vars defined outside any functions and classes  
can be shared between .cpp files(extern)  

## STL Week 3
