
#ifndef PROJECT1_DEFINEVARCOMMAND_H
#define PROJECT1_DEFINEVARCOMMAND_H

#include "Command.h"

using namespace std;

class DefineVarCommand : public Command {
private:
    map<string, string> &symTbl;
    map<string, string> &pathTbl;
public:
    DefineVarCommand(queue<string> &_orders,
                              map<string, string> &symTbl, map<string, string> &pathTbl) : Command(_orders),
    symTbl(symTbl), pathTbl(pathTbl)  {}

    int DefineVarCommand::execute();

    };


#endif //PROJECT1_DEFINEVARCOMMAND_H
