#include "diary.h"
#include "handler.h"
#include "pdlist.h"
#include<algorithm>

pdlistHandler::pdlistHandler(pdlistDiary* pdlistdiary):pdlistdiary(pdlistdiary)
{
    registerCommand("pdlist", &pdlistHandler::handlepdlist);
}

void pdlistHandler::handlepdlist(istringstream& stream) const {
    string args;
    string start_date, end_date;
    
    // read remaining parameters
    // erase space
    getline(stream, args);
    args.erase(remove_if(args.begin(), args.end(), ::isspace), args.end()); 

    // deal with [] or empty
    if (args.empty() || args == "[]") {
        pdlistdiary->pdlist("1.1", "12.31");
        return;
    }

    // check format [start,end]
    if (args.front() != '[' || args.back() != ']') {
        handleInvalid();
        return;
    }

    // extract content
    string content = args.substr(1, args.size()-2);
    size_t comma_pos = content.find(',');

    // check comma position
    if (comma_pos == string::npos || //failure
        comma_pos == 0 || 
        comma_pos == content.size()-1) {
        handleInvalid();
        return;
    }

    // date split
    start_date = content.substr(0, comma_pos);
    end_date = content.substr(comma_pos+1);

    // check date format
    bool valid = true;
    valid &= start_date.empty() ? true : datecheck(start_date);
    valid &= end_date.empty() ? true : datecheck(end_date);
    
    // check date logic
    if (!valid || (start_date.empty() ^ end_date.empty())) {
        handleInvalid();
        return;
    }

    // set default
    if (start_date.empty()) 
    { 
        start_date = "1.1";
        end_date = "12.31";
    }

    // Check if the start date is greater than the end date
    date_comparator comp;
    if (!comp(start_date,end_date)) {
        handleInvalid();
        return;
    }
    // execution
    pdlistdiary->pdlist(start_date, end_date);
}

void pdlistHandler::handleHelp(istringstream& stream) const
{
    string other_input;
    stream >> other_input;
    if(!other_input.empty())
    {
        return handleInvalid();
    }
    cout << "> You are in pdlist.exe" << endl;
    cout << "> `pdlist` to list entities ordered by date." << endl;
    cout << "> `pdlist [<start_date>,<end_date>] to list entities during the period." << endl;
    cout << "> All the dates are in form <month>.<date>,e.g. 5.1." << endl;
    cout << "> `bye` to exit the program." << endl;
}

void pdlistDiary::pdlist(string start_date,string end_date)
{
    // Iterate through the entries and print those within the date range
    bool found = false;
    date_comparator comp;
    for (const auto& entry : entries) {
        const string& date = entry.first;
        const string& content = entry.second;
        if (!comp(date,start_date) && !comp(end_date,date)) //start_date <= date && end_date >= date
        {
            found = true;
            cout << date << endl << content;
        }
    }
    // If no entries are found in the date range, print a message
    if (!found)
        cout << "No entries found." << endl;
}

int main() {
    // Initialize the diary
    pdlistDiary pdlistdiary("diary.txt");
    pdlistHandler pdlisthandler(&pdlistdiary);
    pdlistdiary.hint();
    while(true)
    {
        pdlisthandler.handleInput();
        if(pdlisthandler.is_bye())
            break;
    }
    return 0;
}