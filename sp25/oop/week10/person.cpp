#include "person.h"
#include <cstring>
using namespace std;

Person::Person(const char* s){
    name = new char[::strlen(s) + 1];
    ::strcpy(name,s);
}

Person::~Person() {
    delete [] name;
}

void f(Person p)
{
    
}

int main()
{
    Person p("Name");
    f(p);
}