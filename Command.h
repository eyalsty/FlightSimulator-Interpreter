#ifndef COMMAND_H
#define COMMAND_H

#include <queue>
#include <map>
#include <string>
#include <sstream>
#include <iostream>

#include "SYalgorithm.h"

using namespace std;

class Command {
protected:
    queue<string> &orders;
public:
    explicit Command(queue<string> &_orders) : orders(_orders) {}

    virtual int execute() = 0;

};

class CommandException{
    const char* error = "ERROR! in function: ";
    string funcName;
public:
    CommandException(const string& _funcName): funcName(_funcName){}
    void print(){
        cout << error << funcName << endl;
    }
};

#endif