

#ifndef PROJECT1_SYALGORITHM_H
#define PROJECT1_SYALGORITHM_H

#include "Expression.h"
#include <deque>
#include <string>
#include <map>

using namespace std;

Expression *createExp(deque <string> *tokens);

void initPrecedence(map<char, int> &precedence);

Expression *shuntingYard(string exp);


#endif //PROJECT1_SYALGORITHM_H
