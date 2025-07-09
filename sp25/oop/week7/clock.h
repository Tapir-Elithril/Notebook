#ifndef _CLOCK_H
#define _CLOCK_H

#include "numberdisplay.h"

class Clock{
public:
    Clock(int h,int m):hours(24),minutes(60){
        hours.setValue(h);
        minutes.setValue(m);
    }
    void tick(){
        minutes.dida();
        if(minutes.is_RolledOver()){
            hours.dida();
        } 
    }
private:
    NumberDisplay hours;
    NumberDisplay minutes;
};

#endif