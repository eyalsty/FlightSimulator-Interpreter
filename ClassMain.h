#ifndef CLASSMAIN_H
#define CLASSMAIN_H

// maybe can take those includes down (because of commend).
#include <iostream>
#include <queue>
#include <map>
#include <string>
#include <sstream>
#include <fstream>
#include <regex>

#include "ExpCommand.h"     // new
#include "Command.h"

#include "DefineVarCommand.h"
#include "AssignCommand.h"
#include "WhileCommand.h"
#include "IfCommand.h"
#include "PrintCommand.h"
#include "SleepCommand.h"
//#include "OpenDataServer.h"       // those two headers need
//#include "ConnectCommand"         // need to be implemented!!!!!


#define EOL '\n'

using namespace std;

class ClassMain {
    queue<string> script;
    SymbolTable symbolTable;
    map<string, ExpCommand *> commands;
public:
    ClassMain() {
        initializeExpCommands();
    }

    void lexer(const char *fileName);

    void cleanStartSpaces(string &line);

    void deleteEol(string &line);

    string getFirstWord(const string &line);

// for the lexer function.
    void addLineToVector(string &line);

    void saveOneArgCommand(string line);

    void saveCondition(string line);

    void saveVarCommand(string line);

    void saveConnectCommand(string line);

    void saveServerCommand(string line);

    void saveOther(string line);

    void initializeExpCommands() {
        auto *e = new ExpCommand(new DefineVarCommand(script, symbolTable));
        commands.insert(pair<string, ExpCommand *>("var", e));

        // pay attention - the case of line with a form of: x = 'something'.
        e = new ExpCommand(new AssignCommand(script, symbolTable));
        commands.insert(pair<string, ExpCommand *>("assign", e));

        e = new ExpCommand(new WhileCommand(symbolTable, script));
        commands.insert(pair<string, ExpCommand *>("while", e));

        e = new ExpCommand(new IfCommand(symbolTable, script));
        commands.insert(pair<string, ExpCommand *>("if", e));

        e = new ExpCommand(new PrintCommand(symbolTable, script));
        commands.insert(pair<string, ExpCommand *>("print", e));

        e = new ExpCommand(new SleepCommand(script));
        commands.insert(pair<string, ExpCommand *>("sleep", e));

        /* *
         *
         * the Connect & the OpenDataServer.
         *
         * */
    }

    void parser(const char *fileName) {
        ExpCommand *e;
        lexer(fileName);
        while (!script.empty()) {
            // getting the right command.
            if (symbolTable.isVarExist(script.front())) {
                e = commands.at("assign");
            } else {
                e = commands.at(script.front());
                script.pop();
            }
            // script.pop();

            if (e != nullptr) {
                // calling execute() from calculate().
                e->calculate();
            }
        }
    }

    ~ClassMain() {
        auto i = commands.begin();
        while (i != commands.end()) {
            delete i->second;
            ++i;
        }

        // maybe some other deallocating.
    }
};

#endif