#include <iostream>
using namespace std;

class A {
    int i;
public:
    A(int ii):i(ii) {
        cout << "A(int ii) " << ii << endl;}
    void prt() {cout << i << endl;}
    // A operator+(const A& a) {
    //     cout << "operator+" << endl;
    //     return A(this->i+a.i); 
    // }
    A operator-(){
        return A(-i);
    }
    friend const A operator+(const A& a,const A& b);
};

const A operator+(const A& a,const A& b)
{
    cout << "operator+(const A& a,const A& b)" << endl;
    return A(a.i+b.i);
}

int main()
{
    A a1(1);
    A a2 = 2;
    A a3 = a1 + 3;    //a1.operator+(a2)
    a3.prt();
    a3 = -a3;
    a3.prt();
}