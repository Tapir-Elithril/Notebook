#ifndef _HANDLER_H
#define _HANDLER_H

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include "diary.h"

using namespace std;

bool datecheck(const string& date);

class Handler {
private:
    using CommandHandler = void (Handler::*)(istringstream&) const;
protected:
    map<string, CommandHandler> commandMap;
    template <typename T>
    //allow subclass to register its command
    void registerCommand(const string& cmd, void (T::*handler)(istringstream&) const) {
        // translate subclass command into superclass command
        commandMap[cmd] = static_cast<CommandHandler>(handler);
    }
    virtual void handleHelp(istringstream& stream) const = 0;
    void handleBye(istringstream& stream) const;
    void handleInvalid() const;
    bool bye = false;
public:
    Handler();
    ~Handler() = default;
    void handleInput();
    bool is_bye() const;
};

#endif