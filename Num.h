#ifndef NUM_H
#define NUM_H

#include "Expression.h"

class Num : public Expression {
    double value;
public:
    Num(double _value) : value(_value) {}

    double calculate(){
        return value;
    }
};


#endif
