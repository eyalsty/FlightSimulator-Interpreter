#ifndef PROJECT1_SYALGORITHM_H
#define PROJECT1_SYALGORITHM_H

#include "Expression.h"
#include <deque>
#include <string>
#include <map>

#include "Plus.h"
#include "Minus.h"
#include "Mul.h"
#include "Div.h"
#include "Num.h"
#include "SymbolTable.h"

#include <stack>

using namespace std;

Expression *createExp(deque<string> *tokens);

void initPrecedence(map<char, int> &precedence);

Expression *shuntingYard(string exp);



#endif //PROJECT1_SYALGORITHM_H
