
#ifndef PROJECT1_SYMBOLTABLE_H
#define PROJECT1_SYMBOLTABLE_H

#include <map>
#include <string>
#include <vector>

using namespace std;

class SymbolTable {
private:
    map<string, double> symTbl;
    map<string, string> pathTbl;
    vector <string> splitVars(string s);
public:
    void setVar(string var, double val);

    void setPath(string var, string path);

    double getVal(string var);

    string getPath(string var);

    bool isVarExist(string var);

    bool isPathExists(string var);

    string switchVarsToVals(string s);

    void updateFromSimulator(float num, string path);

    };


#endif //PROJECT1_SYMBOLTABLE_H
