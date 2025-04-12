//cx Week2: A quick tour of c++
#include <iostream>
#include <string>
#include <cmath>

template <typename T,typename Compare>
int min_element(T arr[],int begin,int end,Compare comp)
{
    int min_idx = begin;
    for (int i = begin + 1;i < end;i++)
    {
        if (comp(arr[i],arr[min_idx]))
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

template <typename T,typename Compare>
void selection_sort(T arr[],int n,Compare comp)
{
    for (int i = 0;i < n;i++)
    {
        int min_idx = min_element(arr,i,n,comp);
        if(min_idx != i)
        {
            swap(arr[min_idx],arr[i]);
        }
    }
}

template <typename T>
void print_array(T* arr[],int n)
{
    for (int i = 0;i < n;i++)
    {
        std::cout << *arr[i] << " ";
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

class Shape{
protected:
    double area,perimeter;
public:
    virtual ~Shape(){}//析构函数
    double get_area() const{return area;}
    double get_perimeter() const{return perimeter;}
    virtual void calc_area() = 0;
    virtual void calc_perimeter() = 0;
    virtual std::string name() const = 0;
    friend std::ostream& operator<<(std::ostream&,const Shape&);
};

bool less_shape_area(Shape* s1,Shape* s2){
    return s1->get_area() < s2->get_area();
}

bool less_shape_perimeter(Shape* s1,Shape* s2){
    return s1->get_perimeter() < s2->get_perimeter();
}

bool greater_shape_area(Shape* s1,Shape* s2){
    return s1->get_area() > s2->get_area();
}

bool greater_shape_perimeter(Shape* s1,Shape* s2){
    return s1->get_perimeter() > s2->get_perimeter();
}

std::ostream& operator<<(std::ostream& out,const Shape& s)
{
    return out << "(" << s.name() << ":" << s.area << "," << s.perimeter << ")";
}

class Rectangle : public Shape{
private:
    double w,h;
public:
    Rectangle(double w,double h):w(w),h(h){}
    void calc_area() override{
        //std::cout << "haha\n";
        area = w * h;
    }
    void calc_perimeter() override{
        perimeter = 2 * (w + h);
    }
    std::string name() const override{
        return "Rectangle";
    }
};

const double PI = 3.14;

class Circle : public Shape{
private:
    double r;
public:
    Circle(double r):r(r){}
    void calc_area() override{
        area = PI * r * r;
    }
    void calc_perimeter() override{
        perimeter = 2 * PI * r;
    }
    std::string name() const override{
        return "Circle";
    }
};

class Triangle : public Shape{
private:
    double a,b,c;
public:
    Triangle(double a,double b,double c):a(a),b(b),c(c){}
    void calc_area() override{
        double p = (a + b + c) / 2;
        area = sqrt(p * (p - a) * (p - b) * (p - c));
    }
    void calc_perimeter() override{
        perimeter = a + b + c;
    }
    std::string name() const override{
        return "Triangle";
    }
};

int main()
{
    Shape* arr[] = {new Rectangle(2,3),new Rectangle(5,5),new Circle(3),new Triangle(2,5,4)};
    int n = sizeof(arr) / sizeof(arr[0]);

    for (Shape* s : arr)
    {
        s->calc_area();
        s->calc_perimeter();
    }

    selection_sort(arr, n, less_shape_area);
    print_array(arr, n);
    selection_sort(arr, n, less_shape_perimeter);
    print_array(arr, n);
    selection_sort(arr, n, greater_shape_area);
    print_array(arr, n);
    selection_sort(arr, n, [](Shape* s1,Shape* s2){return s1->get_perimeter() > s2->get_perimeter();});
    print_array(arr, n);

    for(Shape* s : arr)
    {
        delete s;
    }
    return 0;
}