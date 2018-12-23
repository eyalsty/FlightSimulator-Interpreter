#ifndef PROJECT1_EXPCOMMAND_H
#define PROJECT1_EXPCOMMAND_H

#include "Expression.h"
#include "Command.h"

class ExpCommand : public Expression {
    Command *command;
public:
    explicit ExpCommand(Command *_command) : command(_command) {}

    double calculate() {
        return (double) command->execute();
    }
};

#endif