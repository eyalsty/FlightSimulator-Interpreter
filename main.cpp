#include "Command.h"
#include "DefineVarCommand.h"
#include "MainClass.h"
#include "SYalgorithm.h"

#include <stack>
#include <queue>
#include <deque>

using namespace std;

int main() {
    Expression *exp = shuntingYard(string("24/(11-5)+2"));
    double test = exp->calculate();
    return 0;
}