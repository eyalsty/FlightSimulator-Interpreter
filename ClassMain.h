#ifndef CLASSMAIN_H
#define CLASSMAIN_H

#include <sstream>
#include <fstream>
#include <regex>

#include "CommandExpression.h"

#include "DefineVarCommand.h"
#include "AssignCommand.h"
#include "WhileCommand.h"
#include "IfCommand.h"
#include "PrintCommand.h"
#include "SleepCommand.h"
#include "OpenDataServer.h"
#include "ConnectCommand.h"


#define EOL '\r'

using namespace std;

class ClassMain {
    queue<string> script;
    SymbolTable symbolTable;
    map<string, Expression *> commands;
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
        auto *e = new CommandExpression(new DefineVarCommand(script, symbolTable));
        commands.insert(pair<string, Expression *>("var", e));

        // pay attention - the case of line with a form of: x = 'something'.
        e = new CommandExpression(new AssignCommand(script, symbolTable));
        commands.insert(pair<string, Expression *>("assign", e));

        e = new CommandExpression(new WhileCommand(symbolTable, script));
        commands.insert(pair<string, Expression *>("while", e));

        e = new CommandExpression(new IfCommand(symbolTable, script));
        commands.insert(pair<string, Expression *>("if", e));

        e = new CommandExpression(new PrintCommand(symbolTable, script));
        commands.insert(pair<string, Expression *>("print", e));

        e = new CommandExpression(new SleepCommand(script));
        commands.insert(pair<string, Expression *>("sleep", e));

        e =  new CommandExpression(new ConnectCommand(script));
        commands.insert(pair<string, Expression *>("connect", e));

        e =  new CommandExpression(new OpenDataServer(script,symbolTable,new DataReaderServer(symbolTable)));
        commands.insert(pair<string, Expression *>("openDataServer", e));

    }

    void parser(const char *fileName) {
        Expression *e;
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