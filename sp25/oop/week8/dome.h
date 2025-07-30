#ifndef _DO_ME_H_
#define _DO_ME_H_

#include <vector>
// #include "cd.h"
// #include "dvd.h"
#include "item.h"
using namespace std;

class Database{
private:
    // vector<CD> cds;
    // vector<DVD> dvds;
    vector<Item&> items;
public:
    // void addCD(const CD &cd);
    // void addDVD(const DVD &dvd);
    void add(const Item &item);
    void list(void) const;
};

#endif