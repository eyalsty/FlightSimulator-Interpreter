#include "Command.h"
#include "MainClass.h"
#include "SYalgorithm.h"
#include "SleepCommand.h"
#include "PrintCommand.h"
#include "ControlParser.h"
#include "SymbolTable.h"

#include <stack>
#include <queue>
#include <deque>

using namespace std;

int main() {
    SymbolTable *symbols = new SymbolTable;
    symbols->setVar("x", 5.5);
    symbols->setVar("y", 10);
    symbols->setVar("x", 7);

    return 0;
}