#ifndef PLUS_H
#define PLUS_H

#include "BinaryExpression.h"

class Plus : public BinaryExpression {
public:
    Plus(Expression *_left, Expression *_right)
            : BinaryExpression(_left, _right) {};

    virtual double calculate() {
        return left->calculate() + right->calculate();
    }
};


#endif