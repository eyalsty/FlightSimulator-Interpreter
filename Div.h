#ifndef DIV_H
#define DIV_H

#include "BinaryExpression.h"

class Div : public BinaryExpression {
public:
    Div(Expression *_left, Expression *_right)
            : BinaryExpression(_left, _right) {}

    virtual double calculate() {
        if (right->calculate() == 0) {
            throw "ERROR! Division by zero.";
        }
        return left->calculate() / right->calculate();
    }
};


#endif
