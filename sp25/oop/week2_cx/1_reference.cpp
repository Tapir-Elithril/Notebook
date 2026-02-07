//cx Week2: A quick tour of c++
#include <iostream>

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

void swap(int& a,int& b)
//Reference
{
    int temp = a;
    a = b;
    b = temp;
}

void selection_sort(int arr[],int n)
{
    for (int i = 0;i < n;i++)
    {
        // int min_idx = i;
        // for (int j = i + 1;j < n;j++)
        // {
        //     if (arr[j] < arr[min_idx])
        //     {
        //         min_idx = j;
        //     }
        int min_idx = min_element(arr,i,n);
        //     if(min_idx != i)
        //     {
        //         int temp = arr[min_idx];
        //         arr[min_idx] = arr[i];
        //         arr[i] = temp;
        //     }
        // }
        if(min_idx != i)
        {
            swap(arr[min_idx],arr[i]);
        }
    }
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
    int arr[] = {64, 25, 12, 23, 11};
    int n = sizeof(arr) / sizeof(arr[0]);
    selection_sort(arr, n);
    print_array(arr, n);
    return 0;
}