#include "WhileCommand.h"
#include "IfCommand.h"


int WhileCommand::execute() {
    // if the condition is false.
    if (!ControlParser::execute()) {
        // taking out all of the orders from the queue.
        while (whileOrders.front() != "}") {
            whileOrders.pop();
        }
        whileOrders.pop();
    }
    // we initialize the condition at execute() of CondParser.
    isConditionInit = true;

    // empty the while scope from the general queue.
    whileOrders = getOrdersAsQueue();

    // beck up for the while loop queue.
    queue<string> whileScope = whileOrders;

    int x = 0;
    Command *c;
    while (ControlParser::execute()) {
        whileOrders = whileScope;
        // the offset.
        x += 1;
        string token = whileOrders.front();
        /* not popping immidiatlly because
         * of the assign command (x = 3 for example).*/
        if (!symbolTable->isVarExist(token)) {
            whileOrders.pop();
        }
        while (token != "}") {
            if (token == "{") {
                token = whileOrders.front();
                // for the assign command.
                if (!symbolTable->isVarExist(token)) {
                    whileOrders.pop();
                }
                continue;
            }
            c = getCommand(token);
            if (c != nullptr) {
                c->execute();
                delete c;
            } else {
                throw CommandException("while loop!");
            }
            token = whileOrders.front();
            if (!symbolTable->isVarExist(token)) {
                whileOrders.pop();
            }
        }
    }
    /* finished this while command, now we'll need to init again
     * if wed'e like to do another one.*/
    isConditionInit = false;
    return x;
}

queue<string> WhileCommand::getOrdersAsQueue() {
    // getting the orders for the while loop as list.
    queue<string> ordersQueue;
    string token = orders.front();
    orders.pop();
    int counter = 0;
    do {
        if (token == "{") {
            counter++;
        } else if (token == "}") {
            counter--;
        }
        ordersQueue.push(token);
        if (!orders.empty() && counter != 0) {
            token = orders.front();
            orders.pop();
        }
    } while (counter != 0);
    return ordersQueue;
}

Command *WhileCommand::getCommand(const string &name) {
    // returning the right command to be executed.
    if (name == "print") {
        return new PrintCommand(symbolTable, whileOrders);
    } else if (name == "sleep") {
        return new SleepCommand(whileOrders);
    } else if (name == "if") {
        return new IfCommand(symbolTable, whileOrders);
    } else if (symbolTable->isVarExist(name)) {
        return new AssignCommand(whileOrders, symbolTable);
    } else if (name == "while") {
        return new WhileCommand(symbolTable, whileOrders);
    } else if (name == "var") {
        return new DefineVarCommand(whileOrders, symbolTable);
    } else {
        return nullptr;
    }
}