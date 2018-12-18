#ifndef DEFINEVARCOMMAND_H
#define DEFINEVARCOMMAND_H

#include "Command.h"

# define MIN_ARGS 3

class DefineVarCommand : public Command {
    map<string, double> &symbolTable;
public:
    explicit DefineVarCommand(map<string, double> &st):symbolTable(st) {}

    int execute(const vector<string> &v);

    bool isVar(const string &name) const;
};
#endif
