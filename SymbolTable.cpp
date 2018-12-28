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
    pthread_mutex_lock(&m);
    symTbl[var] = val;
    //if we updated a var and its binded to the simulator => send him a message
    if (isPathExists(var)) {
        this->client->sendMessage(pathTbl[var],symTbl[var] );
    }
    pthread_mutex_unlock(&m);

}

void SymbolTable::setPath(string var, string path) {
    pathTbl[var] = path;
}

bool SymbolTable::isVarExist(string var) {
    return symTbl.count(var) > 0;
}

bool SymbolTable::isPathExists(string var) {
    return pathTbl.find(var) != pathTbl.end();
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
            cout << endl << (*it).second << "  " << "updated" << endl;
            this->symTbl[name] = num;
        }
    }
}