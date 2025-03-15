#include<cstdlib>
#include<iostream>
using namespace std;

struct Student{
    int id;
    Student(){
        id = 0;
        cout << "Student::Student(): id = " << id << endl;
    }
    ~Student(){
        cout << "Student::~Student(): id = " << id << endl;
    }
};

int main()
{
    int *pa = new int(1024);
    cout << *pa << endl;

    int *parr = new int[10];
    for(int i = 0;i < 10;i++)
        parr[i] = i;
    for(int i = 0;i < 10;i++)
        cout << parr[i] << " ";
    cout << endl;

    delete pa;
    delete[] parr;

    Student *ps1 = (Student*)malloc(sizeof(Student));
    cout << "ps1->id = " << ps1->id << endl;
    Student *ps2 = new Student;
    cout << "ps2->id = " << ps2->id << endl; 
    
    free(ps1);
    delete ps2;

    Student *psarr = new Student[5];
    for(int i = 0;i < 5;i++)
        psarr[i].id = i;

    delete[] psarr;
}