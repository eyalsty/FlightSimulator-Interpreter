#ifndef CLASSMAIN_H
#define CLASSMAIN_H

#include <sstream>
#include <fstream>
#include <regex>

#include "CommandExpression.h"
#include <unistd.h>
#include "DefineVarCommand.h"
#include "AssignCommand.h"
#include "WhileCommand.h"
#include "IfCommand.h"
#include "PrintCommand.h"
#include "SleepCommand.h"
#include "OpenDataServer.h"
#include "ConnectCommand.h"
#include "SymbolTable.h"


#define EOL '\r'

using namespace std;

class ClassMain {
    queue<string> script;
    SymbolTable *symbolTable;
    map<string, Expression *> commands;
    ConnectCommand *connect;
    DataReaderServer *read;
    pthread_mutex_t mutex;

public:
    ClassMain() {
        pthread_mutex_init(&mutex, nullptr);
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

        this->connect = new ConnectCommand(script, mutex);

        auto *e = new CommandExpression(this->connect);
        commands.insert(pair<string, Expression *>("connect", e));

        this->symbolTable = new SymbolTable(this->connect);

        e = new CommandExpression(new DefineVarCommand(script, this->symbolTable));
        commands.insert(pair<string, Expression *>("var", e));

        // pay attention - the case of line with a form of: x = 'something'.
        e = new CommandExpression(new AssignCommand(script, this->symbolTable, mutex));
        commands.insert(pair<string, Expression *>("assign", e));

        e = new CommandExpression(new WhileCommand(this->symbolTable, script, mutex));
        commands.insert(pair<string, Expression *>("while", e));

        e = new CommandExpression(new IfCommand(this->symbolTable, script, mutex));
        commands.insert(pair<string, Expression *>("if", e));

        e = new CommandExpression(new PrintCommand(this->symbolTable, script));
        commands.insert(pair<string, Expression *>("print", e));

        e = new CommandExpression(new SleepCommand(script));
        commands.insert(pair<string, Expression *>("sleep", e));

        this->read = new DataReaderServer(this->symbolTable, mutex);
        e = new CommandExpression(new OpenDataServer(script,
                                                     this->symbolTable, this->read));
        commands.insert(pair<string, Expression *>("openDataServer", e));
    }

    void parser(const char *fileName) {
        Expression *e;
        lexer(fileName);
        while (!script.empty()) {
            // getting the right command.
            if (symbolTable->isVarExist(script.front())) {
                e = commands.at("assign");
            } else {
                e = commands.at(script.front());
                script.pop();
            }
            //wait until server is connected
            while (!this->read->getIsConnection()) {
                cout << "waiting for client to connect" << endl;
                sleep(3); //wait 3 seconds
                this->connect->setIsConnection(false);
            }
            if (!this->connect->getIsConnection()) {
                cout << "press enter when autoStart is on" << endl;
                cin.ignore();
                cout << "program started" << endl;
            }
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
        pthread_mutex_destroy(&mutex);
        this->connect->setMembers(true, "quit");
        this->read->stop();
        // maybe some other deallocating.
    }
};

#endif