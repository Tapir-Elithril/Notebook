#include<iostream>

using namespace std;

int main()
{
    int a[] = {53,54,55};
    int * const p = a;
    *p = 20;
    for(int i = 0;i < sizeof(a) / sizeof(a[0]); i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
    return 0;
}