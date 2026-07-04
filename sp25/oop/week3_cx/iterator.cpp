#include<iostream>
#include<vector>
#include<iterator>
#include<algorithm>
#include<list>
#include"infix_iterator.h"
using namespace std;

int main()
{
    vector<int> v = {1, 2, 3, 5};
    vector<int> u;
    reverse(v.begin(), v.end());
    copy(v.begin(),v.end(),back_inserter(u));
    copy(u.begin(),u.end(),ostream_iterator<int>(cout, ","));
    cout << endl;
    
    list<int> l;
    copy(v.begin(),v.end(),front_inserter(l));
    copy(l.begin(),l.end(),ostream_iterator<int>(cout, ","));
    cout << endl; 

    copy(v.begin(),v.end(),infix_ostream_iterator<int>(cout, ","));
    cout << endl;
    return 0;
}