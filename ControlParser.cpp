#include "ControlParser.h"

void ControlParser::saveOperandValues(Condition &lg, const string &left,
                                      const string &right) {
    // calculating the left operand (first check if it variable or exp).
    string nLeft = left;
    if (symbolTable->isVarExist(nLeft)) {
        // getting a reference to the var!
        lg.operandL = symbolTable->getVal(left);
    } else {
        Expression *e = shuntingYard(left);
        // it isn't in the map, so its an expression.
        lg.operandL = e->calculate();
        delete e;
    }

    // calculating the right operand (first check if it variable or exp.
    if (symbolTable->isVarExist(right)) {
        // getting a reference to/ the var!
        lg.operandR = symbolTable->getVal(right);
    } else {
        Expression *e = shuntingYard(right);
        lg.operandR = e->calculate();
        delete e;
    }
    // so we can updating their values on run - time.
    lg.nameL = left;
    lg.nameR = right;
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


void ControlParser::updateCondition() {

    /*checks if the values of the condition variables has
     * changed, and updating the condition accordingly.*/

    if (symbolTable->isVarExist(logicExp.nameR)) {
        logicExp.operandR = symbolTable->getVal(logicExp.nameR);
    }
    if (symbolTable->isVarExist(logicExp.nameL)) {
        logicExp.operandL = symbolTable->getVal(logicExp.nameL);
    }
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

string &ControlParser::popOrder() {
    string &y = orders.front();
    if (symbolTable->isVarExist(y)) {
        return y;
    }
    orders.pop();
    return y;
}

void ControlParser::cleanScope() {
    // cleaning the 'if' scope. we need it when the condition == false.
    while (orders.front() != "}") {
        orders.pop();
    }
    orders.pop();       // popping the '}'.
}


int ControlParser::execute() {
    // the condition initialize already, so we need to update it now.
    if (isConditionInit) {
        updateCondition();
        return isCondTrue();
    } else {
        // the condition did not initialize, so now we need to init it.
        initCondition();
        return isCondTrue();
    }
}

