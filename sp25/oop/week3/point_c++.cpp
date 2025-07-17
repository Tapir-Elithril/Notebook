#include<iostream>

using namespace std;

//typedef is no longer needed
struct Point
{
    int x;
    int y;
    void print();
    void move(int dx,int dy);
};

void Point::print()
{
    cout << this << endl;
    cout << this->x << " " << this->y << endl;
    //cout << x << " " << y << endl;
}

void Point::move(int dx,int dy)
{
    x += dx;
    y += dy;
}   

int main()
{
    Point p;
    p.x = 1;
    p.y = 2;
    //cout << p.x << " " << p.y << endl;
    cout << &p << endl;
    p.print();//Point::print(&p);
    Point p2;
    p2.x = 3;
    p2.y = 4;
    cout << &p2 << endl;
    p2.print(); 
    p.move(3,4);
    p.print();
    return 0;
}