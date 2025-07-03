#include<cstdlib>
#include<iostream>
using namespace std;

extern int globalx;
double pi();

int main()
{
    cout << "globalx = " << globalx << endl;
    cout << "pi = " << pi() << endl;
}