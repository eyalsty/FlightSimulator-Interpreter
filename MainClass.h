#ifndef MAINCLASS_H
#define MAINCLASS_H

// maybe can take those includes down (because of commend).
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <fstream>

#include "Command.h"

#define EOL '\n'

using namespace std;

class MainClass {
    vector<string> script;
    map<string, double> symbolTable;
    map<string, Command *> commandTypes;      // have to be  *Command.
public:
    void lexer(const char *fileName);

    void addLineToVector(string &line);
};

#endif
