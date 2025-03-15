#include"integer.h"

void Integer::init(int i)
{
    this->i = i;
    //i = i;(all represent the ::init(int i) because all local var covers global var)
}

Integer* Integer::bigger(Integer* that)
{
    if(that->i > this->i)
        return that;
    else
        return this;
}