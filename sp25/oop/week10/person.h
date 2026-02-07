#ifndef _PERSON_H_
#define _PERSON_H_

class Person {
public:
    Person(const char *s);
    ~Person();
    void print();
private:
    char *name; //char * instead of string
};

#endif