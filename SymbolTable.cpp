
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

