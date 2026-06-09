#ifndef _CD_H
#define _CD_H

#include "item.h"
#include <iostream>
#include <string>
using namespace std;

class CD : public Item {
private:
    string artist;
    int numberoftracks;
    // int playtime;
    // bool gotit;
    // string comment;
public:
    CD(const string& artist,int numberoftracks,int playtime,bool gotit,const string& comment);
    // void print() const;
    // void setComment(const string& comment);
    const string& getArtist() const;
    // const string& getComment() const;
    int getNumberOfTracks() const;
    // int getPlayTime() const;
    // bool getGotIt() const;
    // void setGotIt(bool gotit);
};

#endif