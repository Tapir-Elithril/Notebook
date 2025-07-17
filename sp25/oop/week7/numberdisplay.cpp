#include "numberdisplay.h"

#include<iostream>
using namespace std;
//g++ -D_NUMBER_DISPLAY_TEST_ numberdisplay.cpp -o numberdisplay
#ifdef _NUMBER_DISPLAY_TEST_
int main()
{
    NumberDisplay nd(10);
    cout << nd.getValue() << endl;
    nd.setValue(5);
    for(int i = 0; i < 20; i++){
        nd.dida();
        std::cout << nd.getValue() << std::endl;
    }
    return 0;
}
#endif