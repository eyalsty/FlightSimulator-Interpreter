#ifndef CLASSMAIN_H
#define CLASSMAIN_H

#include <sstream>
#include <fstream>
#include <regex>
#include <unistd.h>

#include "CommandExpression.h"
#include "DefineVarCommand.h"
#include "AssignCommand.h"
#include "WhileCommand.h"
#include "IfCommand.h"
#include "PrintCommand.h"
#include "SleepCommand.h"
#include "OpenDataServer.h"
#include "ConnectCommand.h"
#include "SymbolTable.h"

#define FILE_ERROR "ERROR! could not open file : "
#define WAIT_CLIENT "waiting for a client to connect"
#define WAIT_AUTOSTART "press enter when autoStart is on"
#define STARTED "program started"
#define EOL '\r'

using namespace std;

class ClassMain {
    queue<string> script;
    SymbolTable *symbolTable;
    map<string, Expression *> commands;
    ConnectCommand *connect;
    DataReaderServer *read;
    pthread_mutex_t mutex;

// splitting the line, and push tokens to queue
    void addLineToVector(string &line);

    void cleanStartSpaces(string &line);

    void saveOneArgCommand(string line);

//saving If and While commands in the queue
    void saveCondition(string line);

//saving the defineVarCommand in the queue
    void saveVarCommand(string line);

    void saveConnectCommand(string line);

    void saveServerCommand(string line);

    void saveOther(string line);

    void deleteEol(string &line);

    string getFirstWord(const string &line);

public:
    ClassMain() {
        pthread_mutex_init(&mutex, nullptr);
        initExpressionsMap();
    }

//splitting the file content into tokens in the main queue
    void lexer(const char *fileName);

    void initExpressionsMap();

    //executing the commands of the script according to the Expressions map
    void parser(const char *fileName);

    ~ClassMain() {
        this->connect->stop();   //disconnect the client
        this->read->stop(); //disconnect the server

        auto i = commands.begin();
        while (i != commands.end()) {//free all the commands
            delete i->second;
            ++i;
        }
        delete symbolTable;
        pthread_mutex_destroy(&mutex);         //destroy the mutex

    }
};

#endif