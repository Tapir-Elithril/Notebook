# 面向对象程序设计  

## Using Objects Week 1  
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

string str1; //fixed value('\0') in str1(different from C)
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

## A Quick Tour of C++ Week 2

## STL Week 3
[Definition]Part of the ISO Standard C++ Library,Data Structure and Algorithms  

- Containers:class templates,data structures  
- Algorithms  
- Iterators:uniform access of manners  
  
### Containers

- Sequential:array(static),vector(dynamic),deque(double-ended queue),(forward_)list  
- Associative:set(key),map(key-value),multiset,multimap
- Unordered associative  
- Adaptors:stack,(priority_)queue  
  
#### vector

- Constructor,destructor  
- Element access:at,operator[],front,back,data,...  
- Iterators:begin,end,cbegin,cend,...  
- Capacity:empty,size,reserve,capacity,...  
- Modifiers:clear,insert,erase,push_back,...  

```cpp
vector<int> v;
v[100] = 1; //Whoops!
//use push_back() or resize()
```
  
#### list
(doubly-linked)
`push_back`,`list<string>::iterator p;`

#### map  
`map<string,float> price;`
multi-map:one key corresponds to multiple values

#### stack  
adaptor:转换器  

### Algorithms  

- [first,last)
- for_each,find,count,...  
- copy,fill,transform,replace,rotate,...  
- sort,partial_sort,nth_element,...
- set_difference,set_union,...  
- accumulate,partial_sum,...  

### Iterators  

### Typedefs
`auto`:编译器推断  
`using`  
`typedef map<Name,list<PhoneNum>> PB;`  

## Memory model Week 4
### variables
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
  
global vars:vars defined outside any functions and classes and can be shared between .cpp files(extern)  
  
static vars:inhibit to be accessed outside .cpp
  
static local vars:keep its state btw functions

static  

- restricted access scope  
- persistent storage  
  
### reference
`ps = &s`,`(*ps).length()`,`ps->length()`  
绑定别名，通过引用直接操作原始变量  
```cpp
char* s = p;//a pointer to a character
char& r = q;//a reference

int  x = 47;
int& y = x;
cout << "y = " << y << endl;//y = 47
y = 18;
cout << "x = " << x << endl;//x = 18
y = z;//copy the value of z to y(a.k.a x)
```
```cpp
void f(int &);
f(i * 3)//not allowed
int&* p;//illegal
void f(int*& p);//legal
//no reference to reference
//no array of reference
```
### dynamic memory allocation
```cpp
new int;//malloc
new Stash;
new int[10];

delete p;//free
delete[] p;
```
new and delete triggers and ensures the correctness of Ctor/Dtor  
cannot delete twice but can delete nullptr

### constant
```cpp
const int x = 123;
x = 27; //illegal
x++;    //illegal

int y = x;       //legal,copy const to non-const
y = x;           //legal
const int z = y; //legal
```
`const` is an *internal linkage*

- Compile time constants `const int bufsize = 1024;`  
- Run-time constants
```cpp
const int class_size = 12;  //store in .text
int finalgrade[class_size]; //legal

int x;
cin >> x;

const int size = x;
double classaverage[size]; //error,static array length must be fixed when compiling!
```
```cpp
int a[] = {53,54,55};
int * const p = a;// p(pointer) is a const
*p = 20; //legal
p++;     //illegal

const int *p = a; // (*p)(the object pointer p points to) is a const
*p = 20; //illgal
p++;     //legal
```
```cpp
int i;
const int ci;
int* ip;
const int* cip;
ip = &i;
ip = &ci; //illegal,ci cannot be modified but ip can,this is not allowed
cip = &i;
cip = &ci;
*ip = 54; //always legal
*cip = 54;//never legal
```
String literals:in .text,read only

## Defining Class Week 3(WengKai)
```cpp
void print(Point *p)
void move(Point *p,int dx,int dy)
```
Q1:All the functions take a pointer to Point as the first parameter,why?If we take it as a global var,is it OK?  
ANS:No,because we need to tell the function **which** struct to deal with  
Solution:put the functions into the struct -> member functions class  
`::`所有格resolver
```cpp
void S::f() //function f in class S
{
    ::f(); //global function f,instead of recursively call
    ::a++; //global a
    a--;   //local a
}
```
How does the compiler now its members when executing member functions?  
`this` is a pointer points to the object  

### Object
Object = Attributes + Service = Data(private) + Operations(Public)  
UML:name,attribute,service(operations)  
class≈struct(class默认访问权限为private而struct为public)  
任何class都需要分在.h与.cpp两个文件中，.h提供声明供他人使用，.cpp提供private实体  
**One** class definition **per** header.h
Only declarations are allowed in .h  

- extern var  
- function prototypes  
- class/struct definition 
  
### include  

- # include "xx.h"：优先搜索.cpp文件所在目录再到指定位置搜索
- # include<xx.h>：指定位置搜索
  自带头文件
  环境变量
  -I
- # include<xx>：与<xx.h>相同
  
### Constructor
What will happen if we forget to initialize?  
Without initialization,we won't get fixed value.  
```cpp
struct Point
{
    int x;
    int y;
    Point(int x,int y) // 构造函数
    {
        this->x = x;
        this->y = y;
    }
};

int main()
{
    Point p(1,2);
    Point p2{1,2};
}
构造函数名字与结构名相同，没有返回类型  
没有参数的构造函数：default  
成员变量的赋值  

- 在结构体中赋值  
- 在构造函数头中添加初始化列表`Point(int xx,int yy):x(xx),y(yy)` 成员变量名(初始化值)
- 在构造函数中赋值  
- 以上三种按序进行

```cpp
struct Y
{
    float f;
    int i;
    Y(int a);
}
Y y1[] = {Y(1),Y(2),Y(3)}; //OK
Y y2[2] = {Y(1)}; //ERROR
Y y3[7]; //ERROR
Y y4; //ERROR
```
### Destructor
```cpp
struct Y{
    ~Y();//cannot have any parameter
};
~Y(){
    //auto
    ...
}
```
What happens with `goto` and `switch`?  
Not allowed.  

## Inside Object Week 4(WengKai)
what to do and how to do
### Access Control
  
- public  
- friend:授权（所有）私有成员，被以下接收  
  自由函数  
  类中的函数  
  整个类  
- private:私有的边界是类，不是对象  
  同一类的不同对象可以互相访问private成员    
- protected:子类可以访问  

### Objects in different places
![alt text](image.png)  
![alt text](image-1.png)  
![alt text](image-2.png)  

### Static
Initialization Dependency:not guaranteed  
strong recommend:no global vars!  

- static storage  
- restricted access  
  
use static only inside **functions and classes**

- static free function:deprecated  
- static global vars:deprecated  
- static local vars:persistent storage  
- static member vars:shared  
- static member functions:shared  
  
static object:initialized when first called,destruct as a global var  
static member:不在class的存储空间中，被不同对象共享（被视为同一个）
```cpp
class M{
    static int m_h; //declaration,not belonging to the class
    int m_w; //declaration
};

int M::m_h;
static int M::m_h;//ERROR
```
static function:no `this`,不能访问任何非静态成员变量或函数  
不需要制造对象即可调用，和任何对象都无关  
应用：提供制造类对象的方法，作为制造函数   
