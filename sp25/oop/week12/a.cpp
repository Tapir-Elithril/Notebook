#include <iostream>

using namespace std;

int add(int a, int b)
{
    return a + b;
}

// double add(double a,double b)
// {
//     return a + b;
// }

template <typename T>
T add(T a,T b)
{       
    return a + b;
}

int main()
{       
    cout << add(1,2) << endl;
    cout << add(1.1,2.2) << endl;
    cout << add(1.1,2.2f) << endl;
    return 0;
}       
