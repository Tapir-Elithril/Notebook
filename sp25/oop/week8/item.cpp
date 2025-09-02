#include "item.h"

#include <iostream>
using namespace std;

Item::Item(int playtime, bool gotit, const string& comment)
    : playtime(playtime), gotit(gotit), comment(comment) {}

void Item::print() const {
    cout << "Playtime: " << playtime << endl;
    cout << "Got it: " << (gotit ? "Yes" : "No") << endl;
    cout << "Comment: " << comment << endl;
}

void Item::setComment(const string& comment) {
    this->comment = comment;
}

const string& Item::getComment() const {
    return comment;
}

int Item::getPlayTime() const {
    return playtime;
}

bool Item::getGotIt() const {
    return gotit;
}

void Item::setGotIt(bool gotit) {
    this->gotit = gotit;
}

