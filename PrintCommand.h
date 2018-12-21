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
            // printing a variable value.
            if (symbolTable.isVarExist(orders.front())) {
                cout << symbolTable.getVal(orders.front()) << endl;
                orders.pop();
            } else {
                // printing a string.
                cout << orders.front() << endl;
                orders.pop();
            }
            return NUM_OF_ARGS;
        } else {
            throw CommandException("print");
        }
    }
};

#endif
