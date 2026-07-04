# ifndef _ADVENTURE_H
# define _ADVENTURE_H
#include<vector>
#include<map>
#include<string>

using namespace std;

extern const int direction_num;
extern const string direction[];
extern const map<string, int> direction_to_index;

class IGame;
class Game;
class Handle;
class Room;

//use IGame and inheritance to initialize Game for all the Room
class IGame {
public:
    virtual ~IGame(){};
    virtual bool checkPrincessFound() const = 0; 
    virtual void setPrincessFound() = 0;     
    virtual void set_role() = 0;            
};
    
class Game : public IGame{
private:
    Room* current;
    vector<Room*> rooms; 
    static bool princess_found;
    int room_num;
public:
    Game(int room_num);
    ~Game();
    void hint();
    int output();
    void move(string direction);
    void setPrincessFound() override;
    bool checkPrincessFound() const override;
    void set_role() override;
    Room* getCurrentRoom() const;
};

class Handler {
private:
    Game* game;
    // Create a hash table (unordered_map) to map commands to their respective handler functions
    unordered_map<string, function<bool(istringstream&)>> commandMap;
    bool handleHelp(istringstream& stream) const;
    bool handleGo(istringstream& stream) const;
    bool handleInvalid() const;
public:
    Handler(Game* game);
    ~Handler();
    void handleInput() const;
};
    
class Room {
private:
    IGame* game;
    bool monster;
    bool princess;
    string name;
    Room** exit;
    int exit_num;
public:
    Room(IGame *g ,string name);
    ~Room();
    void set_exits(Room** exit);
    Room* find_exits(const string& direction) const;
    int print_info() const;
    void set_princess();
    void set_monster();
};
          
# endif