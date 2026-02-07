#include<stdlib>
#include<iostream>
#include<thread>

using namespace std;

struct student{
    int id;
    char address[1000];
};

//void foo(student s)
void foo(const student* ps)
{
    cout << ps->id << endl;
}
void bar(const student &s)
{
    cout << s.id << endl;
}
