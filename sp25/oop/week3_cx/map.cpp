#include<iostream>
#include<map>
using namespace std;

int main()
{
    map<string,float> price;
    price["apple"] = 3;
    price["orange"] = 5;
    price["banana"] = 2;

    string item;
    double total = 0;
    while(cin >> item)
    {
        if(price.contains(item))//-std=c++20 or count
            total += price[item];
        else
            cout << item << " is not in the fruit list" << endl;
        //auto creation if not found
    }
    //ctrl + d to end input
    cout << total << endl;

    //pair<string,float>
    for(const auto& pair:price)
        cout << "{" << pair.first << ":" << pair.second << "}";
    cout << endl;
}