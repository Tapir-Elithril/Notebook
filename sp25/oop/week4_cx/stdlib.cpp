#include<cstdlib>
#include<iostream>
using namespace std;

int globalx = 4;

int main()
{
    static int staticx = 3;
    int localx = 5;
    int *px = (int*)malloc(sizeof(int));

    cout << "&globalx = " << &globalx << endl; 
    cout << "&staticx = " << &staticx << endl; 
    cout << "&localx = " << &localx << endl;
    cout << "&px = " << &px << endl;
    cout << "px = " << px << endl; 
}