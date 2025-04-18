#include <iostream>
#include <string>
using namespace std;

static int objectcount = 0;

class HowMany {
public:
    HowMany() {objectcount++; cout << "HowMany()" << endl;}
    HowMany(const HowMany& r) {
        objectcount ++;
        this -> i = r.i;
        cout << "HowMany(HowMany)" << endl;
    }
    void set(int i) {this -> i = i;}
    void print(const string& msg = "") {
        if(msg.size() != 0) cout << msg << ": ";
        cout << "objectcount = " << objectcount << "i=" << i << endl;
    }
    ~HowMany() {objectcount--; cout << "~HowMany()" << endl;}
private:
    int i;
};

HowMany f(HowMany x) {
    cout << &x << endl;
    cout << "begin of f" << endl;
    x.print("x argument inside f()");
    x.set(2);
    cout << "end of f" << endl;
    return x;
}

int main()
{
    HowMany h;
    h.set(1);
    h.print("after construction of h");
    cout << &h << endl;
    HowMany h2 = f(h);
    h.print("after ctor of h");
    h2.print("after ctor of h2");
}