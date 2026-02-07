#include<iostream>
#include<map>
#include<string>
#include<sstream>
#include<algorithm>
#include<random>
#include<cstdlib>
#include "adventure.h"

using namespace std;

const int direction_num = 4;
const string direction[] = {"west","east","up","down"};
const map<string, int> direction_to_index = {
    {"west", 0},
    {"east", 1},
    {"up", 2},
    {"down", 3}
};

//static member initialization
bool Game::princess_found = false;

Game::Game(int room_num)
{
    this->room_num = room_num;
    //Initialize the rooms using new
    rooms.push_back(new Room(this,"Lobby"));
    rooms.push_back(new Room(this,"Room 1"));
    rooms.push_back(new Room(this,"Room 2"));
    rooms.push_back(new Room(this,"Room 3"));
    rooms.push_back(new Room(this,"Room 4"));
    rooms.push_back(new Room(this,"Room 5"));
    //Set exits
    Room* lobby[direction_num] = {rooms[1],rooms[2],rooms[4],nullptr};
    rooms[0]->set_exits(lobby);
    Room* room1[direction_num] = {nullptr,rooms[0],rooms[3],nullptr};
    rooms[1]->set_exits(room1);
    Room* room2[direction_num] = {rooms[0],nullptr,rooms[5],nullptr};
    rooms[2]->set_exits(room2);
    Room* room3[direction_num] = {nullptr,rooms[4],nullptr,rooms[1]};
    rooms[3]->set_exits(room3);
    Room* room4[direction_num] = {rooms[3],rooms[5],nullptr,rooms[0]};
    rooms[4]->set_exits(room4);
    Room* room5[direction_num] = {rooms[4],nullptr,nullptr,rooms[2]};
    rooms[5]->set_exits(room5);
    //Set role
    set_role();
    //start at lobby
    current = rooms[0];
}

Game::~Game()
{
    //Destructor
    //Delete all the new objects
    for(auto& r:rooms)
        delete r;
}

void Game::hint()
{
    cout << "> Game start!" << endl;
    cout << "> Type 'help' if you don't know what to do." << endl;
}

int Game::output()
{
    return current->print_info();
}

void Game::move(string direction)
{
    if(current->find_exits(direction) != nullptr)
        current = current->find_exits(direction);
    else
    {
        cout << "Impasse!" << endl;
        exit(0);
    }
}

void Game::setPrincessFound()
{
    princess_found = true;
}

bool Game::checkPrincessFound() const
{
    return princess_found;
}

void Game::set_role() 
{
    random_device rd;
    mt19937 gen(rd());
    //randomly set in room1-5
    uniform_int_distribution<> dis(1, room_num - 1);
    //monster and princess should not be in the same room
    int room_princess = dis(gen);
    int room_monster = dis(gen);
    int error = 0;
    while(room_princess == room_monster)
    {
        room_monster = dis(gen);
        error ++;
        if(error >= 100)
        {
            cout << "> Something Error!" << endl;
            exit(1);
        }
    }
    rooms[room_princess]->set_princess();
    rooms[room_monster]->set_monster();
}

Room* Game::getCurrentRoom() const 
{ 
    return current; 
}

Handler::Handler(Game* g):game(g)
{
    commandMap["help"] = [this](istringstream& stream) { return handleHelp(stream); };
    commandMap["go"] = [this](istringstream& stream) { return handleGo(stream); };
}

Handler::~Handler()
{
    //Destructor
}

bool Handler::handleHelp(istringstream& stream) const
{
    string other_input;
    stream >> other_input;
    if(!other_input.empty())
    {
        return handleInvalid();
    }
    cout << "> Your goal is to find the princess and bring her out." << endl;
    cout << "> Please input 'go + direction',e.g.'go east'" << endl; 
    return false;
}

bool Handler::handleGo(istringstream& stream) const
{
    string input_direction;
    stream >> input_direction;
    string other_input;
    stream >> other_input;
    if(!other_input.empty())
        return handleInvalid();
    if (find(direction, direction + direction_num, input_direction) == direction + direction_num)
        return handleInvalid();
    else if(game->getCurrentRoom()->find_exits(input_direction) == nullptr)
    {
        cout << "> There is no door! Try again!" << endl;
        return false;
    }
    else 
    {
        cout << "> Moving to " << input_direction << endl;
        game->move(input_direction);
        return true;
    }
}

bool Handler::handleInvalid() const
{
    cout << "> Invalid Input! Try again!" << endl;
    return false;
}

void Handler::handleInput() const
{
    while(true)
    {
        string line;
        if(!getline(cin, line))
        {
            if (cin.eof())  // EOF(Ctrl + D)
            {
                cout << "> Game Exit." << endl;
                exit(0);
            }
            else if (cin.fail())
            {
                cerr << "Input error!" << endl;
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
            bool is_break = it->second(stream);  // Call the appropriate handler
            if (firstWord == "go" && is_break) 
                break;
        } 
        else
            handleInvalid();
    }
}

Room::Room(IGame *g,string name):game(g),name(name)
{
    //Constructor
    exit = new Room*[direction_num];
    for (int i = 0; i < direction_num; ++i) 
        exit[i] = nullptr;  // Initialize the array to nullptr
}

Room::~Room()
{
    //Destructor
    delete[] exit;  // Free the dynamically allocated memory for exit
}

void Room::set_exits(Room** exit) 
{
    exit_num = 0;
    for (int i = 0; i < direction_num; ++i)
    {
        this->exit[i] = exit[i];
        if(exit[i] != nullptr)
            exit_num ++;
    }
}

Room* Room::find_exits(const string& input_direction) const
{
    for (int i = 0; i < direction_num; ++i) 
    {
        if (input_direction == direction[i] && exit[i])
            return exit[i];  
    }
    
    return nullptr; 
}


int Room::print_info() const
{
    if(name == "Lobby" and game->checkPrincessFound())
        return 1;
    else if(monster)
    {
        cout << "> Whoops! Monster here!" << endl;
        return -1;
    }
    else if(princess)
    {
        if(!game->checkPrincessFound())
        {
            game->setPrincessFound();  
            cout << "> Princess:Help me!" << endl;
            cout << "> You:Don't be afraid!" << endl;
            cout << "> Princess:Take me to the lobby." << endl;
        }
    }
    cout << "> Welcome to the " << name <<". There are " << exit_num
         << " exits: ";
    int cnt = 1;
    for(int i = 0;i < direction_num; ++i)
    {
        if(exit[i]!=nullptr)
        {
            cout << direction[i];
            cnt ++;
            if(cnt == exit_num)
                cout << " and ";
            else if(cnt > exit_num)
                break;
            else
                cout << ", ";
        }
    }
    cout << "." << endl;
    cout << "> Enter your command:" << endl;
    return 0;
}

void Room::set_princess()
{
    princess = true;
}

void Room::set_monster()
{
    monster = true;
}

int main()
{
    //Initialize the rooms
    int room_num = 6;
    Game game(room_num);
    Handler handler(&game);
    int judge;
    //Start the game
    game.hint();
    while(true)
    {
        //print_info
        judge = game.output();
        if(judge == 0)
            handler.handleInput();
        else break;        
    }
    if(judge == 1)
    {
        cout << "> You have taken the princess to the lobby!" << endl;
        cout << "> You win!" << endl;
    }
    else if(judge == -1)
        cout << "> Game over!" << endl;
    return 0;
}