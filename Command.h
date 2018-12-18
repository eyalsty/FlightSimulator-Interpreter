#ifndef COMMAND_H
#define COMMAND_H

#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

class Command {
public:
    virtual int execute(const vector<string> &v) = 0;
};

#endif