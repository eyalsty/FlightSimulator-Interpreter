#include "Command.h"
#include "MainClass.h"
#include "SYalgorithm.h"
#include "SleepCommand.h"
#include "PrintCommand.h"
#include "IfCommand.h"
#include "WhileCommand.h"
#include "DefineVarCommand.h"

#include <stack>
#include <queue>
#include <deque>

using namespace std;

int main() {
    queue<string> a;
    SymbolTable b;
    b.setVar("x",-3);
    //a.push("Var");
    a.push("regev");
    a.push("=");
    a.push("-x");
    DefineVarCommand* def = new DefineVarCommand(a,b);
    def->execute();
    double result = b.getVal("regev");

    return 0;
}