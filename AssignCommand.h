#ifndef PROJECT1_ASSIGNCOMMAND_H
#define PROJECT1_ASSIGNCOMMAND_H

#include "Command.h"
#include "SymbolTable.h"

#define ARG_NUM1 3

class AssignCommand : public Command {
    SymbolTable *symbolTable;
public:
    AssignCommand(queue<string> &_orders, SymbolTable *_symbolTable, pthread_mutex_t m)
            : Command(_orders), symbolTable(_symbolTable) {
    }

    int execute() {
        // getting the name of the variable.
        string varName = orders.front();
        orders.pop();

        if (!symbolTable->isVarExist(varName)) {
            throw CommandException("Assign value");
        } else {
            orders.pop();       // for the '='.
            string varValueS = orders.front();
            orders.pop();

            varValueS = symbolTable->switchVarsToVals(varValueS);
            Expression *e = shuntingYard(varValueS);

            // getting the real value of the variable.
            double varValue = e->calculate();

            // setting it at the symbol table.
            symbolTable->setVar(varName, varValue);
            delete e;
        }
        return ARG_NUM1;
    }

};


#endif