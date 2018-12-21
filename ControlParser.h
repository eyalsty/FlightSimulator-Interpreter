#ifndef PROJECT1_CONTROLPARSER_H
#define PROJECT1_CONTROLPARSER_H

#include <list>
#include <algorithm>

#include "Command.h"
#include "SymbolTable.h"

struct Condition {
    double operandL;
    string nameL;
    double operandR;
    string nameR;
    string condOperator;
};

class ControlParser : public Command {
protected:
    SymbolTable &symbolTable;
    Condition logicExp;
    const set<string> conditions = {">", "<", ">=", "<=", "=", "!"};
public:
    ControlParser(SymbolTable &_symbolTable, queue<string> &_orders)
            : Command(_orders), symbolTable(_symbolTable) {
        // setting 'logicExp' values.
        initCondition();
    }

    void saveOperandValues(Condition &lg, const string &left,
                           const string &right);

    void initCondition();

    void updateCondition();

    bool isCondTrue();

    string &popOrder();

    void cleanScope();

    virtual int execute();

    virtual ~ControlParser(){}
};

#endif