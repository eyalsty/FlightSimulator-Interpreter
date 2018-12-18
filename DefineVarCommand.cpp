#include "DefineVarCommand.h"

/*int DefineVarCommand::execute(const vector<string> &v) {
    // assuming that the vector v starting from the var NAME!
    string name;
    double value;
    unsigned int offset;        // the offset which well need to return.

    // we need at least 3 arguments to var (name,'=' and value\s).
    if (v.size() >= MIN_ARGS) {
        if (v[2] == "bind") {
            // needs to do execute(), than save its name & value.

            offset = 4;

            // also another condition for for complex expression.
        } else {
            name = v[0];
            istringstream(v[2]) >> value;
            offset = 3;
        }
        symbolTable.insert(pair<string, double>(name, value));
        return offset;
    } else {
        cout << "ERROR! not enough arguments for commend VAR." << endl;
        return -1;
    }
}

bool DefineVarCommand::isVar(const string &name) const {
    // returning true if there is 'name' var, or false otherwise.
    return symbolTable.find(name) != symbolTable.end();
}*/