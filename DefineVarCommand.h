
#ifndef PROJECT1_DEFINEVARCOMMAND_H
#define PROJECT1_DEFINEVARCOMMAND_H

#include "Command.h"
#include "SymbolTable.h"

using namespace std;

class DefineVarCommand : public Command {
private:
    SymbolTable &symbols;
public:
    DefineVarCommand(queue<string> &_orders, SymbolTable &symbols) : Command(_orders), symbols(symbols)  {}

    int execute();
    void bindTo(string varName, string bindedTo);
    vector<string> splitByOperations(string s);

};


#endif //PROJECT1_DEFINEVARCOMMAND_H
