#ifndef _DVD_H
#define _DVD_H

#include"item.h"
#include<string>
using namespace std;

class DVD :public Item{
private:
    string title;
    string director;
    // int playtime;
    // bool gotit;
    // string comment;
public:
    DVD(const string& title, const string& director, int playtime, bool gotit, const string& comment);
    void print() const;
    // void setComment(const string& comment);
    const string& getTitle() const;
    const string& getDirector() const;
    // const string& getComment() const;
    // int getPlayTime() const;
    // bool getGotIt() const;
    // void setGotIt(bool gotit);
};

#endif