#include<iostream>
using namespace std;
class Base{
protected:
    int x;
public:
    Base(int b=0): x(b) { }
    virtual void display() const {cout << x << endl;}
};
class Derived: public Base{
    int y;
public:
    Derived(int d=0): y(d) { }
    void display() {cout << x << "," << y << endl;}
    //void display() const {cout << x << "," << y << endl;}
};
int main()
{
  Base b(1);
  Derived d(2);
  Base *p = &d; //no copy
  b.display();
  d.display();
  p->display();
  return 0;
}