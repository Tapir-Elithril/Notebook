#include <iostream>
using namespace std;

class A {
public:
    A(){f();}
    virtual void f() { cout << "A::f()" << endl; }
};

class B: public A {
public:
    B(){f();}//rewrite vptr
    void f() { cout << "B::f()" << endl; }
};

int main()
{
    B b;
    //first construct A then construct B
    //A::f() is called because
    //vptr is generated in constructor
    return 0;
}