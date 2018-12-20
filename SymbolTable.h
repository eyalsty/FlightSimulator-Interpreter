
#ifndef PROJECT1_SYMBOLTABLE_H
#define PROJECT1_SYMBOLTABLE_H

#include <map>
#include <string>
using namespace std;

class SymbolTable {
private:
    map<string, double> symTbl;
    map<string, string> pathTbl;
public:
    void setVar(string var, double val);
    void setPath(string var, string path);
    double getVal(string var);
    string getPath(string var);
    bool isVarExist(string var);
    bool isPathExists(string var);
};


#endif //PROJECT1_SYMBOLTABLE_H
