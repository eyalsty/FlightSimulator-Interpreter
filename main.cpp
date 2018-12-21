#include "Command.h"
#include "MainClass.h"
#include "SYalgorithm.h"
#include "SleepCommand.h"
#include "PrintCommand.h"
#include "IfCommand.h"
#include "WhileCommand.h"

#include <stack>
#include <queue>
#include <deque>

using namespace std;

int main() {
    try {
        SymbolTable s;
        s.setVar("x", 35);
        s.setVar("throttle", 40);

        queue<string> orders;
        orders.push("throttle>x");
        orders.push("{");
        orders.push("print");
        orders.push("x");
        orders.push("sleep");
        orders.push("1000");
        orders.push("if");
        orders.push("30<=x");
        orders.push("{");
        orders.push("print");
        orders.push("throttle");
        orders.push("}");
        orders.push("}");

        Command *c = new IfCommand(s, orders);
        c->execute();


        cout << "hello, world! NUMBER 2!!!" << endl;
        delete c;
    } catch (const CommandException &e) {
        e.print();
    }

    return 0;
}