

#include "DefineVarCommand.h"

int DefineVarCommand::execute() {
    // assuming that the vector v starting from the var NAME!
    string name;
    double value;
    unsigned int offset;        // the offset which well need to return.

    string varName = this->orders.front();
    this->orders.pop(); //pop var's name
    this->orders.pop(); //pop " = "

    string check = this->orders.front(); //ssget first var's argument
    this->orders.pop(); //pop first argument
    if (check == "bind") {
        string arg = this->orders.front();
        this->orders.pop(); //pop binded arg
        if (pathTbl.find(arg) != pathTbl.end()) { // bind with other var
            auto i = pathTbl.find(arg);
            pathTbl[varName] = i->second;
            auto it = symTbl.find(arg);
            symTbl[varName] = it->second;
        } else {    //bind with some adress ASSUMING there is no ""
            pathTbl[varName] = arg;
            symTbl[varName] = "0";    //set initialized value to 0
        }
    }

    } else {
        cout << "ERROR! not enough arguments for commend VAR." << endl;
        return -1;
    }
}

bool DefineVarCommand::isVar(const string &name) const {
    // returning true if there is 'name' var, or false otherwise.
    return symbolTable.find(name) != symbolTable.end();
}