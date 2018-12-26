#ifndef PROJECT1_WHILECOMMAND_H
#define PROJECT1_WHILECOMMAND_H

#include "ControlParser.h"
#include "PrintCommand.h"
#include "SleepCommand.h"
#include "AssignCommand.h"
#include "DefineVarCommand.h"

using namespace std;

class WhileCommand : public ControlParser {
    queue<string> whileOrders;
    pthread_mutex_t m;
public:
    WhileCommand(SymbolTable *_symbolTable, queue<string> &_orders, pthread_mutex_t m)
            : ControlParser(_symbolTable, _orders), m(m) {
        //whileOrders = getOrdersAsQueue();
    }

    int execute();

    queue<string> getOrdersAsQueue();

    Command *getCommand(const string &name);
};
#endif