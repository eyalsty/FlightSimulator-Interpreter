#ifndef PROJECT1_SYALGORITHM_H
#define PROJECT1_SYALGORITHM_H

#include <deque>
#include <string>
#include <map>
#include <stack>

#include "Expression.h"
#include "Plus.h"
#include "Minus.h"
#include "Mul.h"
#include "Div.h"
#include "Num.h"


using namespace std;

Expression *createExp(deque<string> *tokens);

void initPrecedence(map<char, int> &precedence);

Expression *shuntingYard(string exp);

#endif