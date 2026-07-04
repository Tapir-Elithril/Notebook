#include "diary.h"
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;    

//Diary::Diary(const string& filename):handler(this),filename(filename)
Diary::Diary(const string& filename):filename(filename)
{
    // File open
    ifstream testFile(filename);
    if (!testFile.is_open()) {
        // create new file if not exists
        ofstream newFile(filename);
        if (!newFile.is_open()) {
            cerr << "Error creating new file: " << filename << endl;
            exit(1);
        }
        cout << "> Created new diary file: " << filename << endl;
        newFile.close();
    } 
    else
        testFile.close();

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        exit(0);
    }
    cout << "> Diary open succeed." << endl;
    
    string current_date;
    vector<string> content_buffer;

    string line;
    // Read in a line
    while (getline(file, line)) 
    {
        // Read in a date
        if (datecheck(line)) 
        {
            // store the content of the previous date
            if (!current_date.empty()) 
            {
                // Join the content buffer into a single string
                entries[current_date] = "";
                // Store the content in the entries map
                for (const auto& content_line : content_buffer) 
                {
                    entries[current_date] += content_line + "\n";
                }
                // Clear the content buffer for the new date
                content_buffer.clear();
            }
            // Read in a new date
            current_date = line;
        } 
        // Read in content
        else if (!line.empty()) 
        {
            content_buffer.push_back(line);
        }
    }
    // Deal with the last date
    if (!current_date.empty() && !content_buffer.empty()) 
    {
        entries[current_date] = "";
        for (const auto& content_line : content_buffer) 
        {
            entries[current_date] += content_line + "\n";
        }
        content_buffer.clear();
    }
}

Diary::~Diary()
{
    // Write the entries to the file
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        exit(0);
    }
    // sort the entries by date


    for (const auto& [date,content] : entries) 
    {
        file << date << endl; // Write the date
        if (!content.empty()) 
        {
            file << content; // Write the content
        }
    }
    // File close
    if(file.is_open())
    {
        file.close();
        if (file.is_open()) {
            cerr << "Error closing file: " << filename << endl;
            exit(0);
        }
        cout << "> Diary close succeed." << endl;
    }
}

void Diary::hint() const
{
    cout << "> Type `help` if you don't know what to do." << endl;
}

// void Diary::handleInput()
// {
//     handler.handleInput();
// }

// bool Diary::is_bye() const
// {
//     return handler.is_bye();
// }