#include "diary.h"
#include "handler.h"
#include "pdadd.h"

pdaddHandler::pdaddHandler(pdaddDiary* pdadddiary):pdadddiary(pdadddiary)
{
    registerCommand("pdadd", &pdaddHandler::handlepdadd);
}

void pdaddHandler::handlepdadd(istringstream& stream) const
{
    string date;
    stream >> date;
    //check whether the date if valid
    if(!datecheck(date))
    {
        handleInvalid();
        return;
    }
    vector<string> content_buffer;
    //read the stream to content until a '.' or EOF
    while(true)
    {
        string line;
        if(!getline(cin,line))
        {   
            if(cin.eof())  // EOF(Ctrl + D)
            {
                break;
            }
            else if (cin.fail())
            {
                cerr << "> Input error!" << endl;
                exit(1);
            }
        }
        if(cin.eof())
        {
            content_buffer.push_back(line);
            break;
        }
        if (line == ".")
            break;
        content_buffer.push_back(line);
    }
    if (content_buffer.empty()) {
        cerr << "> Error: Content cannot be empty!" << endl;
        return;
    }
    //call the function
    pdadddiary->pdadd(date,content_buffer);
    content_buffer.clear();
}

void pdaddHandler::handleHelp(istringstream& stream) const
{
    string other_input;
    stream >> other_input;
    if(!other_input.empty())
    {
        return handleInvalid();
    }
    cout << "> You are in pdadd.exe" << endl;
    cout << "> `pdadd <date>` to add an entity,end by a line with a single `.` or `EOF`(`Ctrl-D` in Unix and `Ctrl-Z` in Windows)." << endl;
    cout << "> All the dates are in form <month>.<date>,e.g. 5.1." << endl;
    cout << "> `bye` to exit the program." << endl;
}

void pdaddDiary::pdadd(string date,vector<string>& content_buffer) 
{
    // Check if the date already exists
    bool exist = false;
    auto it = entries.find(date);
    if (it != entries.end()) 
    {
        exist = true;
    }
    // clear the content of the date
    entries[date] = "";
    for (const auto& content_line : content_buffer) 
    {
        entries[date] += content_line + "\n";
    }
    if(exist)
        cout << "> Replace " << date << endl;
    else
        cout << "> Add " << date << endl;
}

int main() {
    // Initialize the diary
    pdaddDiary pdadddiary("diary.txt");
    pdaddHandler pdaddhandler(&pdadddiary);
    pdadddiary.hint();
    while(true)
    {
        pdaddhandler.handleInput();
        if(pdaddhandler.is_bye())
            break;
    }
    return 0;
}