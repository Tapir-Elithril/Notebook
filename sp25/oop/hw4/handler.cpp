#include "diary.h"
#include "handler.h"
#include <algorithm>
#include <stdexcept>

bool safe_stoi(const string& str, int& result) {
    try {
        size_t pos;
        result = stoi(str, &pos);
        
        // check if the entire string was converted
        if (pos != str.size()) {
            return false;
        }
        return true;
    } 
    catch (const invalid_argument&) {
        return false;  // invalid format
    }
    catch (const out_of_range&) {
        return false;  // out of range
    }
} 

Handler::Handler(){
    commandMap.insert({"help",     &Handler::handleHelp});
    commandMap.insert({"bye",      &Handler::handleBye});
}

//check whether the date is valid
bool datecheck(const string& date)
{
    size_t dot_pos = date.find('.');
    if(dot_pos == string::npos || dot_pos == 0 || dot_pos == date.size() - 1)
        return false;
    int month = 0; 
    safe_stoi(date.substr(0, dot_pos),month);
    int day = 0;
    safe_stoi(date.substr(dot_pos + 1),day);
    //check if the month is valid
    if(month < 1 || month > 12)
        return false;
    //check if the day is valid
    if(day < 1 || day > 31)
        return false;
    //check if the day is valid for the month
    if((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
        return false;
    if(month == 2)
    {
        if(day >= 29)
        {
            return false;
        }
    }
    if((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && day > 31)
        return false;
    return true;
}

void Handler::handleHelp(istringstream& stream) const
{
    string other_input;
    stream >> other_input;
    if(!other_input.empty())
    {
        return handleInvalid();
    }
    cout << "> `pdadd <date>` to add an entity,end by a line with a single `.` or `EOF`(`Ctrl-D` in Unix and `Ctrl-Z` in Windows)." << endl;
    cout << "> `pdlist` to list entities ordered by date." << endl;
    cout << "> `pdlist [<start_date>,<end_date>] to list entities during the period." << endl;
    cout << "> `pdshow <date>` to print the content specified by the date." << endl;
    cout << "> `pdremove <date>` to remove one entity of the date. " << endl;
    cout << "> All the dates are in form <month>.<date>,e.g. 5.1." << endl;
    cout << "> `bye` to exit the program." << endl;
}

void Handler::handleBye(istringstream& stream) const
{
    string other_input;
    stream >> other_input;
    if(!other_input.empty())
    {
        return handleInvalid();
    }
    cout << "> Bye~!" << endl;
}

void Handler::handleInvalid() const
{
    cout << "> Invalid Input! Try again!" << endl;
}

void Handler::handleInput()
{
    while(true)
    {
        string line;
        if(!getline(cin, line))
        {
            if (cin.eof())  // EOF(Ctrl + D)
            {
                cout << "> Bye~!" << endl;
                bye = true;
                break;
            }
            else if (cin.fail())
            {
                cerr << "> Input error!" << endl;
                exit(1);
            }
        }
        istringstream stream(line);
        string firstWord;
        stream >> firstWord;
        //check if the input is valid
        //Use hash table to check and call the correct handler
        auto it = commandMap.find(firstWord);
        if (it != commandMap.end()) 
        {
            (this->*(it->second))(stream);  // Call the appropriate handler
            if (firstWord == "bye") 
            {
                bye = true;
                break;  // Exit the loop if "bye" command is executed
            }
        } 
        else
            handleInvalid();
    }
}

bool Handler::is_bye() const
{
    return bye;
}