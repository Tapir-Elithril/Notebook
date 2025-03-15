#include<iostream>

using namespace std;

typedef struct
{
    int x;
    int y;
} Point;

void print(Point *p)
{
    cout << p->x << " " << p->y << endl;
}

void move(Point *p,int dx,int dy)
{
    p->x += dx;
    p->y += dy;
}   

int main()
{
    Point p;
    p.x = 1;
    p.y = 2;
    //cout << p.x << " " << p.y << endl;
    print(&p);
    move(&p,3,4);
    print(&p);
    return 0;
}