#include "clock.h"

int main()
{
    Clock clock(0,0);
    for(int i=0;i<100000;i++){
        clock.tick();
        //cout << clock.print() << endl;
    }
}