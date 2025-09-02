#include<cstdlib>
#include<iostream>
using namespace std;

void access_count()
{
    static int count = 0;
    cout << "access count: "<< count++ << endl;
}

int main()
{
    for(int i = 0; i < 10; i++)
        access_count();
}