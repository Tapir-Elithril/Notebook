#include <iostream>
#include <regex>//正则表达式
using namespace std;

int main()
{
    string s = "hello world";
    regex re("a|e|i|o|u");
    string sl = regex_replace(s, re, "*");
    //h*ll* w*rld
    cout << s << "\n" << sl << endl;
}