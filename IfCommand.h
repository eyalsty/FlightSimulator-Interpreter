#ifndef PROJECT1_IFCOMMAND_H
#define PROJECT1_IFCOMMAND_H

#include "ControlParser.h"
#include "PrintCommand.h"
#include "SleepCommand.h"
#include "AssignCommand.h"
#include "DefineVarCommand.h"

class WhileCommand;//forward declaration

class IfCommand : public ControlParser {
public:
    IfCommand(SymbolTable *_symbolTable, queue<string> &_orders)
            : ControlParser(_symbolTable, _orders) {}

    // consider moving this method to 'ControlParser' base Class.
    Command *getCommand(const string &name);

    int execute();
};

#endif