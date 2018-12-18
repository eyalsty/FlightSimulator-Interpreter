#ifndef COMMAND_H
#define COMMAND_H

#include <queue>
#include <map>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

class Command {
    queue<string> &orders;
public:
    Command(queue<string> &_orders) : orders(_orders){}
    virtual int execute() = 0;
};

#endif