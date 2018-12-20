#include "Command.h"
#include "MainClass.h"
#include "SYalgorithm.h"
#include "SleepCommand.h"
#include "PrintCommand.h"
#include "ControlParser.h"
#include "SymbolTable.h"
#include "DefineVarCommand.h"

#include <stack>
#include <queue>
#include <deque>

using namespace std;

int main() {

/*
    Expression *exp = shuntingYard("-5/10");
    double result = exp->calculate();
    */
    queue<string> a;
    SymbolTable b;
    b.setVar("regev", 3);
    a.push("eyal");
    a.push("=");
    a.push("-regev");
    //a.push("regev*(3+5)");
    DefineVarCommand *def = new DefineVarCommand(a, b);
    def->execute();
    double result = b.getVal("eyal");

    return 0;
}