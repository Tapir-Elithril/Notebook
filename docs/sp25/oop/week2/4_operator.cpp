//cx Week2: A quick tour of c++
#include <iostream>
#include <string>

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

    // //member function
    // bool operator<(const Student& s) const
    // {
    //     return id < s.id;
    // }
    // //operator:算子，第一个元素为自身，故省略
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

int main()
{
    Student arr[] = {{2011,"Newton"},{2001,"Gauss"},{2134,"Euler"},{2067,"Riemann"},{2054,"Mozi"}};
    int n = sizeof(arr) / sizeof(arr[0]);
    selection_sort(arr, n);
    print_array(arr, n);
    return 0;
}