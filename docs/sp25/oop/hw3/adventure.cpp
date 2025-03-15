#include<iostream>
#include<map>
#include<string>
#include<sstream>
#include "room.h"

using namespace std;

//static member initialization
int monster_num = 0;
int princess_num = 0;
bool princess_found = false;

room::room()
{

}

room::~room()
{
    //destructor
}

int main()
{
    //Initialize the rooms
    //TBD(new)

    //Start the game
    while(true){
        //print_info
        string choice;
        string line;
        getline(cin, line);
        stringstream ss(line);
        //check if the input is valid

        //check if the choice is valid
        
    }
    cout << "You win!" << endl;
    return 0;
}