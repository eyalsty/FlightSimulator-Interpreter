#include "IfCommand.h"
#include "WhileCommand.h"

int IfCommand::execute() {
    int offset = 1;
    Command *c;
    // checks if the condition of the 'if' is 'true'
    if (ControlParser::execute()) {
        // getting the name of the command from queue.
        string y = popOrder();
        offset += 1;
        while (y != "}") {
            if (y == "{") {
                y = popOrder();
                offset++;
                continue;
            }
            // getting the command object.
            c = getCommand(y);
            if (c != nullptr) {
                offset += c->execute();
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
    // for the next 'IF' block.
    isConditionInit = false;

    return offset;
}

Command *IfCommand::getCommand(const string &name) {
    // returning the right command to be executed.
    if (name == "print") {
        return new PrintCommand(symbolTable,orders);
    } else if (name == "sleep") {
        return new SleepCommand(orders);
    } else if (name == "if") {
        return new IfCommand(symbolTable, orders);
    } else if(symbolTable->isVarExist(name)) {
        return new AssignCommand(orders, symbolTable);
    } else if(name == "while") {
        return new WhileCommand(symbolTable, orders);
    } else if(name == "var"){
        return new DefineVarCommand(orders,symbolTable);
    } else {
        return nullptr;
    }
}