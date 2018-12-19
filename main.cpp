#include "Command.h"
#include "MainClass.h"
#include "SYalgorithm.h"
#include "SleepCommand.h"
#include "PrintCommand.h"
#include "ControlParser.h"

#include <stack>
#include <queue>
#include <deque>

using namespace std;

int main() {
    map<string, double> symbols;
    symbols.insert(pair<string, double>("x", -83));
    symbols.insert(pair<string, double>("throttle", 83));
    queue<string> orders;
    orders.push("throttle!=x");
    Command *c = new ControlParser(symbols, orders);
    cout << (c->execute() ? "true" : "false") << endl;

    cout << "hello, world!" << endl;

    return 0;
}