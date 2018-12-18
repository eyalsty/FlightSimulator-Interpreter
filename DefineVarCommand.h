#ifndef DEFINEVARCOMMAND_H
#define DEFINEVARCOMMAND_H

#include "Command.h"

# define MIN_ARGS 3

class DefineVarCommand : public Command {

public:
    explicit DefineVarCommand(queue<string> &_orders)
    : Command(_orders) {}

    int execute();

    bool isVar(const string &name) const;
};
#endif
