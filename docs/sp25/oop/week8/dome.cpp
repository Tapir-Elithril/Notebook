#include "dome.h"

#include <iostream>
using namespace std;

// void Database::addCD(const CD &cd) {
//     cds.push_back(cd);
// }

// void Database::addDVD(const DVD &dvd) {
//     dvds.push_back(dvd);
// }

// void Database::list(void) const {
//     cout << "CDs:" << endl;
//     for (const auto& cd : cds) {
//         cd.print();
//         cout << endl;
//     }
    
//     cout << "DVDs:" << endl;
//     for (const auto& dvd : dvds) {
//         dvd.print();
//         cout << endl;
//     }
// }

void Database::add(const Item &item) {
    items.push_back(item);
}

void Database::list(void) const {
    cout << "Items:" << endl;
    for (const auto& item : items) {
        item.print();
        cout << endl;
    }
}