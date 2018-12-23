#ifndef PROJECT1_WHILECOMMAND_H
#define PROJECT1_WHILECOMMAND_H

#include "ControlParser.h"
#include "PrintCommand.h"
#include "SleepCommand.h"
#include "IfCommand.h"
#include "AssignCommand.h"
#include "DefineVarCommand.h"

using namespace std;

class WhileCommand : public ControlParser {
    queue<string> whileOrders;
public:
    WhileCommand(SymbolTable &_symbolTable, queue<string> &_orders)
            : ControlParser(_symbolTable, _orders) {
        whileOrders = getOrdersAsQueue();
    }

    int execute();

    queue<string> getOrdersAsQueue();

    Command *getCommand(const string &name);
};
#endif