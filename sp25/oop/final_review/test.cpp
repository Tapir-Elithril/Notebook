#include <iostream>
using namespace std;
class C1
{
public:
    C1() {
        cout << "$C1()$";
    }
    C1(const C1& a) {
        cout << "$C1(const C1&)$";
    }
    virtual ~C1() {
        cout << "$~C1()$";
    }
};
class C2 : public C1
{
public:
    C2() {
        cout << "$C2()$";
    }
    ~C2() {
        cout << "$~C2()$";
    }
};
int main()
{
    C2* pC2 = new C2();
    cout << endl;
    {
        C1 a = *pC2;
        cout << endl;
    }
    C1* pC1 = pC2;
    delete pC1;
    cout << endl;
}
