#include <iostream>
#include <string>
using namespace std;

class Mammal {
public:
    virtual void Define() {
        cout << "I'm a Mammal\n";
    }
};

class Human : public Mammal {
public:
    void Define() {
        cout << "I'm a Human\n";
    }
};

class Male : public Human {
public:
    void Define() {
        cout << "I'm a Male\n";
    }
};

class Female : public Human {
public:
    void Define() {
        cout << "I'm a Female\n";
    }
};

int main(int argc, char const *argv[]) {
    Mammal *M = new Mammal();
    Male m;
    Female f;
    *M = m; // 对象切片
    //对象切片只有在对象的赋值时才会发生,子类对象赋值给父类指针
    M->Define();
    M = &m; // 多态
    M->Define();
    return 0;
}

#include <iostream>
using namespace std;

class Employee {
public:
    Employee() {
        cout << "Employee ctor called" << endl;
    }

    virtual ~Employee() {
        cout << "Employee dtor called" << endl;
    }

    virtual void show() const {
        cout << "Employee::show()" << endl;
    }
};

class Manager : public Employee {
public:
    Manager() {
        cout << "Manager ctor called" << endl;
    }

    ~Manager() {
        cout << "Manager dtor called" << endl;
    }

    void show() const override {
        cout << "Manager::show()" << endl;
    }
};

void display(Employee* b) {
    b->show(); 
}

int main() {
    Employee* b = new Manager(); //没有发生对象切片
    display(b); 

    delete b; 
    return 0;
}