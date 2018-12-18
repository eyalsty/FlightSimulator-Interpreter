#ifndef MINUS_H
#define MINUS_H

#include "BinaryExpression.h"

class Minus : public BinaryExpression {
public:
    Minus(Expression *_left, Expression *_right)
            : BinaryExpression(_left, _right) {}

    virtual double calculate() {
        return left->calculate() - right->calculate();
    }
};


#endif
