#ifndef PROJECT1_EXPCOMMAND_H
#define PROJECT1_EXPCOMMAND_H

#include "Expression.h"
#include "Command.h"

class CommandExpression : public Expression {
    Command *command;
public:
    explicit CommandExpression(Command *_command) : command(_command) {}

    double calculate() {
        return (double) command->execute();
    }

    ~CommandExpression() {
        delete (this->command);
    }
};

#endif