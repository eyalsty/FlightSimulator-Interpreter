
#include "SymbolTable.h"

//ASSUMING VAR EXISTS ALREADY
double SymbolTable::getVal(string var) {
    auto i = symTbl.find(var);
    double value = i->second;
    return value;
}

string SymbolTable::getPath(string var) {
    auto i = pathTbl.find(var);
    string path = i->second;
    return path;
}

void SymbolTable::setVar(string var, double val) {
    symTbl[var] = val;
    //if we updated a var and its binded to the simulator => send him a message
    if (isPathExists(var)) {
        string sValue = to_string(symTbl[var]);
        this->client->setMembers(true, pathTbl[var] + sValue + "\r\n");
    }
}

void SymbolTable::setPath(string var, string path) {
    pathTbl[var] = path;
}

bool SymbolTable::isVarExist(string var) {
    if (symTbl.find(var) != symTbl.end()) {
        return true;
    }
    return false;
}

bool SymbolTable::isPathExists(string var) {
    if (pathTbl.find(var) != pathTbl.end()) {
        return true;
    }
    return false;
}

string SymbolTable::switchVarsToVals(string s) {
    string temp;
    string expressionS;
    //get vector splitted by digits,operations and var names
    vector<string> splitted = splitVars(s);
    //switch all vars to their values
    for (int i = 0; i < splitted.size(); ++i) {
        temp = "";
        if (isVarExist(splitted[i])) {//check if its a var
            temp = to_string(getVal(splitted[i]));
        } else {
            temp = splitted[i];
        }
        expressionS += temp;
    }
    return expressionS;
}
//split the string by operations
vector<string> SymbolTable::splitVars(string s) {
    vector<string> splitted;
    string buffer;
    set<char> operations = {'+', '-', '/', '*'};
    for (int i = 0; i < s.length(); ++i) {
        //if its some binary operation, split
        if ((operations.find(s[i]) != operations.end()) || s[i] == ')') {
            if (buffer != "") {
                splitted.push_back(buffer);
                buffer = "";
            }
            splitted.push_back(string(1, s[i]));
        } else if (s[i] == '(') {
            splitted.push_back(string(1, s[i])); //push as is
        } else {
            buffer += s[i];
        }
    }
    if (buffer != "")
        splitted.push_back(buffer);
    return splitted;
}

void SymbolTable::updateFromSimulator(double num, string path) {
    for (auto it = this->pathTbl.begin(); it != this->pathTbl.end(); ++it) {
        if (!(it->second.compare(path))) {
            string name = (*it).first;
            //m.lock();
            this->symTbl[name] = num;
            // m.unlock();
        }
    }
}