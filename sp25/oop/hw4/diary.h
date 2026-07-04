# ifndef _DIARY_H
# define _DIARY_H

#include <string>
#include <vector>
#include <map>
#include "handler.h"

using namespace std;

bool datecheck(const string& date);

struct date_comparator 
{
    bool operator()(const string& a, const string& b) const 
    {
        // Parse month and day from "month.day"
        auto parseDate = [](const string& date) -> pair<int, int> 
        {
            size_t dotPos = date.find('.');
            int month = stoi(date.substr(0, dotPos));
            int day = stoi(date.substr(dotPos + 1));
            return {month, day};
        };

        auto [aMonth, aDay] = parseDate(a);
        auto [bMonth, bDay] = parseDate(b);

        if (aMonth != bMonth)
            return aMonth < bMonth;  // Compare months first
        else
            return aDay < bDay;      // If months are equal, compare days
    }
};

class Diary {
private:
protected:
    map<string,string,date_comparator> entries;
    const string& filename;
public:
    Diary(const string& filename);
    ~Diary();
    void hint() const;
};

# endif