#ifndef MUL_H
#define MUL_H

#include "BinaryExpression.h"

class Mul : public BinaryExpression {
public:
    Mul(Expression *_left, Expression *_right)
            : BinaryExpression(_left, _right) {}

    virtual double calculate() {
        return left->calculate() * right->calculate();
    }
};


#endif
