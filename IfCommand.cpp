#include "IfCommand.h"

int IfCommand::execute() {
    int x = 0;
    Command *c;
    // checks if the condition of the 'if' is 'true'
    if (ControlParser::execute()) {
        x += 1;
        // getting the name of the command from queue.
        string y = popOrder();
        while (y != "}") {
            if (y == "{") {
                y = popOrder();
                continue;
            }
            // getting the command object.
            c = getCommand(y);
            if (c != nullptr) {
                c->execute();
                delete c;
            } else {
                throw CommandException(" If condition!");
            }
            // getting the next order for execute.
            y = popOrder();
        }
    } else {
        cleanScope();   //cleaning the 'if' scope because it false.
    }
    return x;
}

Command *IfCommand::getCommand(const string &name) {
    // returning the right command to be executed.
    if (name == "print") {
        return new PrintCommand(symbolTable,orders);
    } else if (name == "sleep") {
        return new SleepCommand(orders);
    } else if (name == "if") {
        return new IfCommand(symbolTable, orders);
    } else if(symbolTable.isVarExist(name)) {
        return new AssignCommand(orders, symbolTable);
    } else if(name == "while"){
        return new WhileCommand(symbolTable,orders);
    } else {
        return nullptr;
    }
}