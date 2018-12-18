#ifndef BINARYEXPRESSION_H
#define BINARYEXPRESSION_H

#include "Expression.h"

class BinaryExpression : public Expression {
protected:
    Expression *left;
    Expression *right;
public:
    BinaryExpression(Expression *_left, Expression *_right)
    : left(_left), right(_right) {}

    virtual double calculate() = 0;

    virtual ~BinaryExpression(){
        // deallocate memory, maybe needs to be changed.
        delete left;
        delete right;
    }
};


#endif
