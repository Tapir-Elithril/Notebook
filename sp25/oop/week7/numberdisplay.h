#ifndef _NUMBER_DISPLAY_H
#define _NUMBER_DISPLAY_H

class NumberDisplay {
public:
    NumberDisplay(int lim):limit(lim){};
    void setValue(int v){
        this->value = v;
    } 
    int getValue() const{
        return this->value;
    }
    //int dida() return 1/value
    void dida(){
        //mutex
        value += 1;
        rolledOver = false;
        if(value == limit){
            value = 0;
            rolledOver = true;
            //hour.dida();
        }
    }
    int is_RolledOver(){
        return rolledOver;
    }
private:
    const int limit;
    int value = 0;
    //NumberDisplay *phour = NumberDisplay(24);
    bool rolledOver = false;
};

#endif