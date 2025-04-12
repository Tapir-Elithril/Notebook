#include "cd.h"

#include <iostream>
using namespace std;

CD::CD(const string& artist, int numberoftracks, int playtime, bool gotit, const string& comment)
    : Item(playtime,gotit,comment),artist(artist), numberoftracks(numberoftracks) {}

void CD::print() const {
    cout << "Artist: " << artist << endl;
    cout << "Number of Tracks: " << numberoftracks << endl;
    Item::print();
    // cout << "Playtime: " << playtime << endl;
    // cout << "Got it: " << (gotit ? "Yes" : "No") << endl;
    // cout << "Comment: " << comment << endl;
}

const string& CD::getArtist() const {
    return artist;
}

int CD::getNumberOfTracks() const {
    return numberoftracks;
}
