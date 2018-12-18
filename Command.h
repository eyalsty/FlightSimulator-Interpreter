#ifndef COMMAND_H
#define COMMAND_H

#include <queue>
#include <map>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

class Command {
protected:
    queue<string> &orders;
public:
    explicit Command(queue<string> &_orders) : orders(_orders) {}

    virtual int execute() = 0;

};

#endif