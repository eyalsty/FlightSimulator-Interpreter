#ifndef PROJECT1_PRINTCOMMAND_H
#define PROJECT1_PRINTCOMMAND_H

#include "Command.h"
#include "SymbolTable.h"

#define NUM_OF_ARGS 1

class PrintCommand : public Command {
    SymbolTable &symbolTable;
public:
    explicit PrintCommand(SymbolTable &_symbolTable, queue<string> &_orders)
            : Command(_orders), symbolTable(_symbolTable) {}

    int execute() {
        if (!orders.empty()) {
            // its a string.
            if (orders.front().find('\"') != string::npos) {
                cout << orders.front() << endl;
                orders.pop();
            } else {
                // its a value of a variable.
                string varValueS =
                        symbolTable.switchVarsToVals(orders.front());
                orders.pop();
                Expression* e = shuntingYard(varValueS);
                cout << e->calculate() << endl;
                delete e;
            }
            return NUM_OF_ARGS;
        } else {
            throw CommandException("print");
        }
    }
};

#endif
