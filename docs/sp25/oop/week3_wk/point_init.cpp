#include<iostream>

using namespace std;

//typedef is no longer needed
struct Point
{
    int x;
    int y;
    Point(int x,int y)
    {
        this->x = x;
        this->y = y;
        cout << "ctor of Point" << endl;
        print();
    }
    ~Point()
    {
        cout << "dtor of Point" << endl;
        print();
    }   
    void print();
    void move(int dx,int dy);
};

void Point::print()
{
    //cout << this << endl;
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
    Point p(1,2);
    {
        // // Point p(1,2);
        // // Point p{1,2};
        // // p.x = 1;
        // // p.y = 2;
        // // //cout << p.x << " " << p.y << endl;
        // // cout << &p << endl;
        // // p.print();//Point::print(&p);
        Point p2{3,4};
        cout << 1 << endl;
        // // p2.x = 3;
        // // p2.y = 4;
        // // cout << &p2 << endl;
        // // p2.print(); 
        // // p.move(3,4);
        // p.print();
        // p2.print();
    } //dtor of p2
    cout << 2 << endl;
    return 0;
}//dtor of p1