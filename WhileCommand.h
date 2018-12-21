#ifndef PROJECT1_WHILECOMMAND_H
#define PROJECT1_WHILECOMMAND_H

#include "ControlParser.h"
#include "PrintCommand.h"
#include "SleepCommand.h"
#include "IfCommand.h"

class WhileCommand : public ControlParser {
public:
    WhileCommand(SymbolTable &_symbolTable, queue<string> &_orders)
            : ControlParser(_symbolTable, _orders) {}

    // NEED to be checked ! only after controlling 'SYalgorithm' for handle variables !
    int execute() {
        int x = 0;
        Command *c;
        while (ControlParser::execute()) {
            x += 1;
            string y = popOrder();
            orders.push(y);
            while (y != "}") {
                if (y == "{") {
                    y = popOrder();
                    orders.push(y);
                    continue;
                }

                c = getCommand(y);
                if (c != nullptr) {
                    c->execute();
                    delete c;
                } else {
                    throw CommandException("While Loop!");
                }
                // getting the next order.
                y = popOrder();
                orders.push(y);
            }
        }
        return x;
    }

    Command *getCommand(const string &name) {
        // returning the right command to be executed.
        if (name == "print") {
            return new PrintCommand(symbolTable, orders);
        } else if (name == "sleep") {
            return new SleepCommand(orders);
        } else if (name == "if") {
            return new IfCommand(symbolTable, orders);
        } else {
            return nullptr;
        }
    }
};


#endif