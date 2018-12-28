#ifndef PROJECT1_WHILECOMMAND_H
#define PROJECT1_WHILECOMMAND_H

#include "ControlParser.h"
#include "PrintCommand.h"
#include "SleepCommand.h"
#include "AssignCommand.h"
#include "DefineVarCommand.h"

using namespace std;

class IfCommand; //foward declaration

class WhileCommand : public ControlParser {
    queue<string> whileOrders;
public:
    WhileCommand(SymbolTable *_symbolTable, queue<string> &_orders)
            : ControlParser(_symbolTable, _orders) {
    }

    int execute();

    queue<string> getOrdersAsQueue();

    Command *getCommand(const string &name);
};
#endif