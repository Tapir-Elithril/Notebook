//cx Week2: A quick tour of c++
#include <iostream>
#include <string>

//function template: 函数模板
template <typename T>//类型参数
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

int main()
{
    std::string arr[] = {"hello","world","zju","boys","girls"};
    int n = sizeof(arr) / sizeof(arr[0]);
    selection_sort(arr, n);
    print_array(arr, n);
    return 0;
}