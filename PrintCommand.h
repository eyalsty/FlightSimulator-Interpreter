#ifndef PROJECT1_PRINTCOMMAND_H
#define PROJECT1_PRINTCOMMAND_H

#include "Command.h"

#define NUM_OF_ARGS 1

class PrintCommand : public Command {
public:
    explicit PrintCommand(queue<string> &_orders) : Command(_orders) {}

    int execute(){
        if(!orders.empty()) {
            cout << orders.front() << endl;
            orders.pop();
            return NUM_OF_ARGS;
        }else {
            throw CommandException("print");
        }
    }
};

#endif //PROJECT1_PRINTCOMMAND_H
