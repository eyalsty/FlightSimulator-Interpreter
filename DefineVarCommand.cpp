

#include "DefineVarCommand.h"

int DefineVarCommand::execute() {
    // assuming that the vector v starting from the var NAME!
    unsigned int offset;        // the offset which well need to return.

    string varName = this->orders.front();
    this->orders.pop(); //pop var's name
    this->orders.pop(); //pop " = "

    string check = this->orders.front(); //sget first var's argument
    this->orders.pop(); //pop first argument
    if (check == "bind") {
        string arg = this->orders.front();
        this->orders.pop(); //pop binded arg
        bindTo(varName, arg); //bind the new var to arg
        offset = 4;
    } else { //check if not "bind", and can be like: "3+y/5..."
        check = this->symbols->switchVarsToVals(check);
        Expression *exp = shuntingYard(check);
        double value = exp->calculate();
        symbols->setVar(varName, value);
        delete exp;
        offset = 3;
    }
    return offset;
}

void DefineVarCommand::bindTo(string varName, string bindedTo) {
    if (this->symbols->isVarExist(bindedTo)) { // bind with existing var
        double argValue = symbols->getVal(bindedTo);
        symbols->setVar(varName, argValue); //set its value in symbol table
        string argPath = symbols->getPath(bindedTo);
        symbols->setPath(varName, argPath); //set its path in path table
    } else {    //bind with some adress ASSUMING there are no ""
        symbols->setVar(varName, 0);  //set initialized value to 0
        symbols->setPath(varName, bindedTo);
    }
}