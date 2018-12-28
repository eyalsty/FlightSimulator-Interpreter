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

    void addLineToVector(string &line); // for the lexer function.
    void cleanStartSpaces(string &line);

    void saveOneArgCommand(string line);

    void saveCondition(string line);

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

    void lexer(const char *fileName);

    void initExpressionsMap();

    void parser(const char *fileName);

    //Destructor
    ~ClassMain() {
        this->connect->stop();   //disconnect the client
        this->read->stop(); //disconnect the server

        // JOIN OTHER THREADS
        pthread_join(connect->getThread(), nullptr);
        pthread_join(read->getThread(), nullptr);


        auto i = commands.begin();
        while (i != commands.end()) {//free all the commands
            delete i->second;
            ++i;
        }
        delete symbolTable;
        pthread_mutex_destroy(&mutex);         //destroy the mutex

        // maybe some other deallocating.
        cout << "all freed" << endl;
    }
};

#endif