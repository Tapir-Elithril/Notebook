#ifndef _ITEM_H_
#define _ITEM_H_

#include <iostream>
#include <string>
using namespace std;

class Item {
private:
    int playtime;
    bool gotit;
    string comment;
public:
    Item(int playtime,bool gotit,const string& comment);
    void print() const;
    void setComment(const string& comment);
    const string& getComment() const;
    int getPlayTime() const;
    bool getGotIt() const;
    void setGotIt(bool gotit);
};

#endif