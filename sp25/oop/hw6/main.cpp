#include <iostream>
#include <string>
#include "vector.h"
#include <cassert>

using namespace std;

class A {
public:
    A(int ii) : i(ii) {cout << "A ctor called for " << i << endl;}
    A():i(0){cout << "A ctor called for " << i << endl;}
    ~A() { cout << "A destructor called for " << i << endl; }
    int geti() { return i; }
    friend ostream& operator<<(ostream& os, const A& a) {
        os << a.i;  
        return os;
    }
private:
    int i;
};

template <typename T>
void printVector(Vector<T>& v) {
    for (int i = 0; i < v.size(); ++i) {
        cout << v.at(i) << " ";
    }
    cout << endl;
}

int main() {
    cout << "===== TEST1: Constructor and Basic Operations =====" << endl;

    // Default constructor
    Vector<int> v1;
    cout << "v1 (empty): " << (v1.empty() ? "True" : "False") << endl;
    assert(v1.empty());

    // Constructor with size 3
    Vector<int> v2(3);
    cout << "v2 size: " << v2.size() << endl;
    assert(v2.size() == 3);
    cout << "v2: ";
    printVector(v2);

    // Push back elements
    v2[0] = 10;
    v2[1] = 20;
    cout << "After assigning 10 and 20 to v2: ";
    printVector(v2);
    cout << "v2 size: " << v2.size() << endl;
    assert(v2.size() == 3);

    // Constructor with initial capacity 0
    Vector<int> v3;
    cout << "v3 (size 0): " << (v3.empty() ? "True" : "False") << endl;
    assert(v3.empty());
    v3.push_back(30);
    cout << "After pushing 30 to v3: ";
    printVector(v3);
    cout << "Size of v3: " << v3.size() << endl;

        // Testing copy constructor
        Vector<int> v4 = v2;
        cout << "v4 (copy of v2): ";
        printVector(v4);
        assert(v4.size() == v2.size());

    cout << "\n===== TEST2: Testing push_back and inflate (capacity expansion) =====" << endl;
    Vector<int> v5;
    cout << "v5 initial size: " << v5.size() << ", capacity: " << 1 << endl;
    for (int i = 1; i <= 20; ++i) {
        v5.push_back(i);
    }
    cout << "v5 after pushing 20 elements: ";
    printVector(v5);

    cout << "\n===== TEST3: Testing with string type =====" << endl;
    Vector<string> v6;
    v6.push_back("hello");
    v6.push_back("world");
    cout << "v6 after pushing strings: ";
    printVector(v6);

    cout << "\n===== TEST4: Testing with class A type =====" << endl;
    Vector<A> v7;
    v7.push_back(A(1));
    cout << "an inflate is done,2 ctors and 1 destructor in total." << endl;
    v7.push_back(A(2));
    cout << "another inflate is done,3 ctors and 2 destructors in total." << endl;
    cout << "v7 after pushing A objects: ";
    printVector(v7);

    cout << "\n===== TEST5: Testing clear and empty =====" << endl;
    Vector<int> v8(5);
    cout << "v8 before clear: ";
    printVector(v8);
    v8.clear();
    cout << "v8 after clear: " << (v8.empty() ? "True" : "False") << endl;
    assert(v8.empty());
    v8.push_back(100);
    cout << "v8: ";
    printVector(v8);

    cout << "\n===== TEST6: Testing `at` with out-of-bounds access =====" << endl;
    try {
        Vector<int> v9(3);
        cout << "Initialization of v9(3)" << endl;
        cout << "v9[0]: " << v9.at(0) << endl;
        cout << "v9[5]: " << v9.at(5) << endl;
    } catch (const out_of_range& e) {
        cout << "Exception: " << e.what() << endl;
    }

    cout << "\n===== TEST7: Testing `[]` with out-of-bounds access =====" << endl;
    try {
        cout << "Initialization of v10(3)" << endl;
        Vector<int> v10(3);
        cout << "v10[0]: " << v10[0] << endl;
        cout << "v10[-1]: " << v10[-1] << endl;
        cout << "v10[5]: " << v10[5] << endl;  
    } catch (const out_of_range& e) {
        cout << "Exception: " << e.what() << endl;
    }

    cout << "\n===== Test Succeed =====" << endl;
    return 0;
}
