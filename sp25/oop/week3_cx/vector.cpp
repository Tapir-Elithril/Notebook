#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int> evens = {2, 4, 6, 8, 10};
    evens.push_back(20);
    evens.push_back(22);
    evens.insert(evens.begin() + 4, 5, 10);

    // for(int i = 0;i < evens.size();i++)
    //     cout << evens[i] << " ";
    // for(vector<int>::iterator it = evens.begin();it < evens.end();it++)
    //     cout << *it << " ";
    // for(int e:evens)
    //         cout << e << " ";
    for(auto it = begin(evens);it != end(evens);it++)
        cout << *it << " ";
    cout << endl;
}