#ifndef PROJECT1_CONTROLPARSER_H
#define PROJECT1_CONTROLPARSER_H

#include <list>
#include <set>
#include <algorithm>

#include "Command.h"

struct Condition {
    double operandL;
    double operandR;
    string condOperator;
};

class ControlParser : public Command {
    map<string, double> &symbolTable;
    //list<string> scopeCommands;
    Condition logicExp;
    const set<string> conditions = {">", "<", ">=", "<=", "=", "!"};
public:
    ControlParser(map<string, double> &_symbols, queue<string> &_orders)
            : Command(_orders), symbolTable(_symbols) {
        // setting the condition value.
        initCondition();
    }

    void saveOperandValues(Condition &lg, const string &left,
                           const string &right);

    void initCondition();


    bool isCondTrue();

    virtual int execute();
};
#endif