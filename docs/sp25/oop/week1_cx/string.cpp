#include <iostream>
#include <string>
using namespace std;

int main()
{
    string str1("This is a test");
    cout << str1 << endl;

    string str2;
    str2 = str1.substr(1,5);
    //the function substr is placed on the object str1
    //功能作用在对象str1上

    cout << str2 << endl;

    string str3;
    str3 = str1.assign("Hello World");
    cout << str3 << endl;
    cout << str1 << endl;
    return 0;
}