#include "ControlParser.h"

void ControlParser::saveOperandValues(Condition &lg, const string &left,
                                      const string &right) {
    // calculating the left operand (first check if it variable or exp).
    if (symbolTable.find(left) != symbolTable.end()) {
        // getting a reference to the var!
        lg.operandL = symbolTable[left];
    } else {
        // it isn't in the map, so its an expression.
        lg.operandL = shuntingYard(left)->calculate();
    }

    // calculating the right operand (first check if it variable or exp.
    if (symbolTable.find(right) != symbolTable.end()) {
        // getting a reference to the var!
        lg.operandR = symbolTable[right];
    } else {
        lg.operandR = shuntingYard(right)->calculate();
    }
}

void ControlParser::initCondition() {
    // to know which operand are we dealing with(left or right).
    bool isLeft = true;

    // getting the logic expression from the queue.
    string exp = orders.front();
    orders.pop();
    string left, right;

    for (int i = 0; i < exp.size(); ++i) {
        // if the char is an operator.
        if (conditions.find(string(1, exp[i])) != conditions.end()) {
            // the case when the operator is '==', '!=' '>=' and '<='.
            if (i < exp.size() && exp[i + 1] == '=') {
                ostringstream ss;
                ss << exp[i] << exp[++i];
                logicExp.condOperator = ss.str();
            } else {
                logicExp.condOperator = string(1, exp[i]);
            }
            isLeft = false;
        } else {
            if (isLeft) {
                // saves the char for getting the left operand.
                left += exp[i];
            } else {
                // saving the char for getting the right operand;
                right += exp[i];
            }
        }
    }
    saveOperandValues(logicExp, left, right);
}


bool ControlParser::isCondTrue() {
    // mapping the string operator to its value, and returning the answer.
    if (logicExp.condOperator == ">") {
        return logicExp.operandL > logicExp.operandR;
    } else if (logicExp.condOperator == "<") {
        return logicExp.operandL < logicExp.operandR;
    } else if (logicExp.condOperator == ">=") {
        return logicExp.operandL >= logicExp.operandR;
    } else if (logicExp.condOperator == "<=") {
        return logicExp.operandL <= logicExp.operandR;
    } else if (logicExp.condOperator == "==") {
        return logicExp.operandL == logicExp.operandR;
    } else {
        return logicExp.operandL != logicExp.operandR;
    }
}

int ControlParser::execute() {
    return isCondTrue();
}