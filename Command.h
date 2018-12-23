#ifndef COMMAND_H
#define COMMAND_H

#include <queue>
#include <map>
#include <string.h>
#include <sstream>
#include <iostream>
#include <set>

#include "SYalgorithm.h"

using namespace std;

class Command {
protected:
    queue<string> &orders;
public:
    explicit Command(queue<string> &_orders) : orders(_orders) {}

    virtual int execute() = 0;

    virtual ~Command(){};

};

class CommandException {
    const char *error = "ERROR! in function: ";
    string funcName;
public:
    // getting the name of the function with the Error.
    CommandException(const string &_funcName) : funcName(_funcName) {}

    void print() const {
        cout << error << funcName << endl;
    }
};

#endif