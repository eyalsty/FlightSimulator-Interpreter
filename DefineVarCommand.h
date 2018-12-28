#ifndef PROJECT1_DEFINEVARCOMMAND_H
#define PROJECT1_DEFINEVARCOMMAND_H

#include "Command.h"
#include "SymbolTable.h"

using namespace std;

class DefineVarCommand : public Command {
private:
    SymbolTable *symbols;

    void bindTo(string varName, string bindedTo);

public:
    DefineVarCommand(queue<string> &_orders, SymbolTable *symbols):
    Command(_orders), symbols(symbols) {}

    int execute();

};

#endif //PROJECT1_DEFINEVARCOMMAND_H
