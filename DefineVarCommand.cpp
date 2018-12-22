

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

    } else { //check is not "bind", and can be like: "3+y/5..."
        check = this->symbols.switchVarsToVals(check);
        double value = shuntingYard(check)->calculate();
        symbols.setVar(varName, value);
    }
    return 1;
}

void DefineVarCommand::bindTo(string varName, string bindedTo) {
    if (this->symbols.isVarExist(bindedTo)) { // bind with existing var
        string argPath = symbols.getPath(bindedTo);
        symbols.setPath(varName, argPath);
        double argValue = symbols.getVal(bindedTo);
        symbols.setVar(varName, argValue);
    } else {    //bind with some adress ASSUMING there are no ""
        symbols.setPath(varName, bindedTo);
        symbols.setVar(varName, 0);  //set initialized value to 0
    }
}



//OLD CODE FOR BACKUP: (SPLIT BY OPERATIONS)

/*
vector<string> splitted;
string buffer;
set<char> operations = {'+', '-', '/', '*'};
for (int i = 0; i < s.length(); ++i) {
    //if negative number
    if ((s[i] == '-') && (buffer == "")) {
        buffer += s[i];
    }
    //if its some binary operation, split
    else if ((operations.find(s[i]) != operations.end()) || s[i] == ')') {
        if (buffer != "")
            splitted.push_back(buffer);
        splitted.push_back(string(1, s[i]));
        buffer = "";
    } else if (s[i] == '(') {
        splitted.push_back(string(1, s[i])); //push as is
    } else {
        buffer += s[i];
    }
}
splitted.push_back(buffer);
return splitted;
 */

