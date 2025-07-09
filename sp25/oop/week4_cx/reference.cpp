#include<iostream>
using namespace std;
void f(int *x)
{
    (*x)++;
}

void g(int& x)
{
    x++;
}

int x;

int& h()
{
    int q;
    return x;
}

int main()
{
    int a = 0;
    f(&a);
    cout << "a = " << a << endl;
    g(a);
    cout << "a = " << a << endl;
    h() = 16;
}