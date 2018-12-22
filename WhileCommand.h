#ifndef PROJECT1_WHILECOMMAND_H
#define PROJECT1_WHILECOMMAND_H

#include "ControlParser.h"
#include "PrintCommand.h"
#include "SleepCommand.h"
#include "IfCommand.h"
#include "AssignCommand.h"

class WhileCommand : public ControlParser {
    queue<string> whileOrders;
public:
    WhileCommand(SymbolTable &_symbolTable, queue<string> &_orders)
            : ControlParser(_symbolTable, _orders) {
        whileOrders = getOrdersAsQueue();
    }

    // NEED to be checked ! only after controlling 'SYalgorithm' for handle variables !
    int execute() {
        // beck up for the while loop queue.
        queue<string> whileScope = whileOrders;
        int x = 0;
        Command *c;
        if (!ControlParser::execute()) {
            cleanScope();
        }
        while (ControlParser::execute()) {
            whileOrders = whileScope;
            x += 1;
            string token = whileOrders.front();
            if (!symbolTable.isVarExist(token)) {
                whileOrders.pop();
            }
            while (token != "}") {
                if (token == "{") {
                    token = whileOrders.front();
                    if (!symbolTable.isVarExist(token)) {
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
                if (!symbolTable.isVarExist(token)) {
                    whileOrders.pop();
                }
            }
        }
        return x;
    }

    queue<string> getOrdersAsQueue() {
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
            if (!orders.empty()) {
                token = orders.front();
                orders.pop();
            }
        } while (counter != 0);
        return ordersQueue;
    }

    Command *getCommand(const string &name) {
        // returning the right command to be executed.
        if (name == "print") {
            return new PrintCommand(symbolTable, whileOrders);
        } else if (name == "sleep") {
            return new SleepCommand(whileOrders);
        //} else if (name == "if") {
        //    return new IfCommand(symbolTable,whileOrders);
        } else if (symbolTable.isVarExist(name)) {
            return new AssignCommand(whileOrders, symbolTable);
        } else if (name == "while") {
            return new WhileCommand(symbolTable, whileOrders);
        } else {
            return nullptr;
        }
    }
};


#endif