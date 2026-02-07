#include "dvd.h"
#include "item.h"

#include <iostream>
using namespace std;

DVD::DVD(const string& title, const string& director, int playtime, bool gotit, const string& comment)
    : Item(playtime,gotit,comment),title(title), director(director) {}

void DVD::print() const {
    cout << "Title: " << title << endl;
    cout << "Director: " << director << endl;
    Item::print();
}


const string& DVD::getTitle() const {
    return title;
}

const string& DVD::getDirector() const {
    return director;
}