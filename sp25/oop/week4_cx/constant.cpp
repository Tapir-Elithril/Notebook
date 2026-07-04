#include<cstdlib>
#include<iostream>
#include<thread>
using namespace std;

int main()
{
    const char *s = "Hello, world!";
    // char *s  == const char *s 
    // s[0] = 'B'; // error
    char s2[] = "Hello, world!";
    char s3[] = "Hello, world!";

    cout << (void*)s << endl;
    cout << (void*)s2 << endl;
    cout << (void*)s3 << endl;
    cout << (void*)main << endl;
    s2[0] = 'B';
    cout << s2 << endl;
}