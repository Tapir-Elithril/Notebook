//cx Week2: A quick tour of c++
#include <iostream>

int min_element(double arr[],int begin,int end)
//[begin,end)
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

int min_element(int arr[],int begin,int end)
//[begin,end)
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
//同名函数overloading: 函数名相同，参数列表不同
//函数重载

void swap(double& a,double& b)
//Reference
{
    double temp = a;
    a = b;
    b = temp;
}

void swap(int& a,int& b)
//Reference
{
    int temp = a;
    a = b;
    b = temp;
}

void selection_sort(double arr[],int n)
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

void selection_sort(int arr[],int n)
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

void print_array(double arr[], int n)
{
   for (int i = 0;i < n;i++)
   {
        std::cout << arr[i] << " ";
   }
        std::cout << std::endl;
}

void print_array(int arr[], int n)
{
   for (int i = 0;i < n;i++)
   {
        std::cout << arr[i] << " ";
   }
        std::cout << std::endl;
}

int main()
{
    double arr[] = {64.1, 25.3, 12.2, 23.5, 11.7};
    int n = sizeof(arr) / sizeof(arr[0]);
    selection_sort(arr, n);
    print_array(arr, n);
    return 0;
}