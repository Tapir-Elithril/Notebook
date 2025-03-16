# ifndef _ROOM_H
# define _ROOM_H
#include<map>
#include<string>

using namespace std;

class game {

};

class room {
private:
    bool monster;
    bool princess;
public:
    static int monster_num;
    static int princess_num;
    static bool princess_found;
    bool lobby;
    string name;
    room();
    ~room();
    map<string, bool>exit[4];
    int exit_num;
    void print_info();
};

# endif