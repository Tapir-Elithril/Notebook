#include<iostream>
#include<string>
#include "vector.h"

using namespace std;

class A{
public:
    A(){cout << "A()" << endl;}
    A& operator=(const A& a) {
        if(this != &a)
            cout << "A& operator=(const A& a)" << endl;
        return *this;
    }
private:
    static const int size = 10;
    int a[size];//sizeof(A) is unknown unless static const
};

// void f(Vector<int> &v)
// {
//     cout << v.size << endl;
// }

int main() {
    Vector<int> v(10);
    //f<int>(v);
    for (int i = 0; i < 10; i++)
        v[i] = i;
    for (int i = 0; i < 10; i++)
        cout << v[i] << endl;
    Vector<string> vs(10);
    for (int i = 0; i < 10; i++)
        vs[i] = "hello";
    Vector<A> va(10);//ctor already done
    cout << "-------------" << endl;
    for (int i = 0; i < 10; i++)
    {
        A a;
        va[i] = a;//overloaded operator assignment
    }
    return 0;
}