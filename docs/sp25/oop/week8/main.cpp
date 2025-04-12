#include "cd.h"
#include "dvd.h"
#include "dome.h"
#include <iostream>

using namespace std;

int main(){
    Database db;
    CD cd1("Artist1", 10, 60, true, "Great CD");
    DVD dvd1("Movie1", "Director1", 120, false, "Interesting movie");
    db.add(cd1);
    db.add(dvd1);
    db.list();
    return 0;
}