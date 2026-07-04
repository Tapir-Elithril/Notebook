#include<iostream>

using namespace std;

class shape {
    //int i = 1;
public:
    //void render() {cout << "shape::render()" << endl;}
    //void render() {cout << "shape::render()" << i << endl;}
    virtual void render() {cout << "shape::render()" << endl;}
    //dynamic binding by using `virtual`
};

class rectangle : public shape {
    int i = 2;
public:
    void render() {cout << "rectangle::render()" << i << endl;}
};

class ellipse : public shape {
    int i = 3;
public:
    void render() {cout << "ellipse::shape()" << i << endl;}
};

void draw(shape* p)//p is pointer to shape
{
    p->render();//shape.render() without `virtual`
}

int main()
{
    rectangle r;
    ellipse e;
    cout << sizeof(shape) << endl;
    cout << sizeof(rectangle) << endl;
    draw(&r);
    r.render();
    shape* p = &r;
    p->render();
    shape s;
    shape* q = &s;
}