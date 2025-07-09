#include "diary.h"
#include "handler.h"
#include "pdshow.h"

pdshowHandler::pdshowHandler(pdshowDiary* pdshowdiary):pdshowdiary(pdshowdiary)
{
    registerCommand("pdshow",&pdshowHandler::handlepdshow);
}

void pdshowHandler::handlepdshow(istringstream& stream) const
{
    string date;
    stream >> date;
    //check whether the date if valid
    if(!datecheck(date))
    {
        handleInvalid();
        return;
    }
    //call the function
    pdshowdiary->pdshow(date);
}

void pdshowHandler::handleHelp(istringstream& stream) const
{
    string other_input;
    stream >> other_input;
    if(!other_input.empty())
    {
        return handleInvalid();
    }
    cout << "You are in pdshow.exe" << endl;
    cout << "> `pdshow <date>` to print the content specified by the date." << endl;
    cout << "> All the dates are in form <month>.<date>,e.g. 5.1." << endl;
    cout << "> `bye` to exit the program." << endl;
}

void pdshowDiary::pdshow(string date)
{
    // Check if the date exists in the entries
    auto it = entries.find(date);
    if (it != entries.end()) {
        cout << it->second;
    } 
    else
    // If the date does not exist, print a message
        cout << "> Contents Not Found!" << endl;
}

int main() {
    // Initialize the diary
    pdshowDiary pdshowdiary("diary.txt");
    pdshowHandler pdshowhandler(&pdshowdiary);
    pdshowdiary.hint();
    while(true)
    {
        pdshowhandler.handleInput();
        if(pdshowhandler.is_bye())
            break;
    }
    return 0;
}