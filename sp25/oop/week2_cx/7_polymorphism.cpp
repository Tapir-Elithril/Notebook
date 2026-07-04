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
void print_array(T* arr[],int n)
{
    for (int i = 0;i < n;i++)
    {
        std::cout << *arr[i] << " ";
        //specialization
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
    virtual void calc_area() = 0;
    virtual void calc_perimeter() = 0;
    virtual std::string name() const = 0;
    friend std::ostream& operator<<(std::ostream&,const Shape&);
};

std::ostream& operator<<(std::ostream& out,const Shape& s)
{
    return out << "(" << s.name() << ":" << s.area << "," << s.perimeter << ")";
}

class Rectangle : public Shape{
//Rectangle is inherit from Shape
private:
    double w,h;
    //double area,perimeter;
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
    //double area,perimeter;
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
    //double area,perimeter;
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

    // selection_sort(arr, n);
    print_array(arr, n);
    return 0;
}