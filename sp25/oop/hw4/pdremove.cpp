#include "diary.h"
#include "handler.h"
#include "pdremove.h"

pdremoveHandler::pdremoveHandler(pdremoveDiary* pdremovediary):pdremovediary(pdremovediary)
{
    registerCommand("pdremove", &pdremoveHandler::handlepdremove);
}

void pdremoveHandler::handlepdremove(istringstream& stream) const
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
    pdremovediary->pdremove(date);
}

void pdremoveHandler::handleHelp(istringstream& stream) const
{
    string other_input;
    stream >> other_input;
    if(!other_input.empty())
    {
        return handleInvalid();
    }
    cout << "> You are in pdremove.exe" << endl;
    cout << "> `pdremove <date>` to remove one entity of the date. " << endl;
    cout << "> All the dates are in form <month>.<date>,e.g. 5.1." << endl;
    cout << "> `bye` to exit the program." << endl;
}

int pdremoveDiary::pdremove(string date)
{
    // Check if the date exists in the entries
    auto it = entries.find(date);
    if (it != entries.end()) {
        entries.erase(it);  // Remove the entry
        cout << "> remove succeed!" << endl;
        return 0;  // Success
    } 
    else {
        cout << "> remove fail!" << endl;
        cout << "> Contents not found!" << endl;
        return -1;  // failure
    }
}

int main() {
    // Initialize the diary
    pdremoveDiary pdremovediary("diary.txt");
    pdremoveHandler pdremovehandler(&pdremovediary);
    pdremovediary.hint();
    while(true)
    {
        pdremovehandler.handleInput();
        if(pdremovehandler.is_bye())
            break;
    }
    return 0;
}