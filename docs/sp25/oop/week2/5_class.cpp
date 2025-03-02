//cx Week2: A quick tour of c++
#include <iostream>
#include <string>
#include <cmath>

template <typename T>
int min_element(T arr[],int begin,int end)
{
    int min_idx = begin;
    for (int i = begin + 1;i < end;i++)
    {
        if (arr[i] < arr[min_idx])
        {
            min_idx = i;
        }
    }
    return min_idx;
}

template <typename T>
void swap(T& a,T& b)
{
    T temp = a;
    a = b;
    b = temp;
}

template <typename T>
void selection_sort(T arr[],int n)
{
    for (int i = 0;i < n;i++)
    {
        int min_idx = min_element(arr,i,n);
        if(min_idx != i)
        {
            swap(arr[min_idx],arr[i]);
        }
    }
}

template <typename T>
void print_array(T arr[],int n)
{
    for (int i = 0;i < n;i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

struct Student{
    int id;
    std::string name;
};

bool operator<(const Student& s1,const Student& s2)
{
    //return s1.id < s2.id;
    return s1.name < s2.name;
}

std::ostream& operator<<(std::ostream& out,const Student& s)
{
    return out << "(" << s.id << "," << s.name << ")";
}

//struct是默认public的class
class Rectangle{
private://user cannot access directly
//Encapsulation:封装
    double w,h;
    double area,perimeter;
public:
    Rectangle(double w,double h):w(w),h(h){}
    //Constructor:构造函数 for initialization
    void calc_area(){
        area = w * h;
    }
    void calc_perimeter(){
        perimeter = 2 * (w + h);
    }
};

const double PI = 3.14;

class Circle{
private:
    double r;
    double area,perimeter;
public:
    Circle(double r):r(r){}
    void calc_area(){
        area = PI * r * r;
    }
    void calc_perimeter(){
        perimeter = 2 * PI * r;
    }
};

class Triangle{
private:
    double a,b,c;
    double area,perimeter;
public:
    Triangle(double a,double b,double c):a(a),b(b),c(c){}
    void calc_area(){
        double p = (a + b + c) / 2;
        area = sqrt(p * (p - a) * (p - b) * (p - c));
    }
    void calc_perimeter(){
        perimeter = a + b + c;
    }
};

int main()
{
    Rectangle arr[] = {Rectangle(2,3),Rectangle(5,5)};
    Circle arr2[] = {Circle(3)};
    Triangle arr3[] = {Triangle(2,5,4)};
    int n = sizeof(arr) / sizeof(arr[0]);

    for (Rectangle& r : arr)
    {
        r.calc_area();
        r.calc_perimeter();
    }

    selection_sort(arr, n);
    print_array(arr, n);
    return 0;
}