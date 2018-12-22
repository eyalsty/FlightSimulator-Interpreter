#ifndef CLASSMAIN_H
#define CLASSMAIN_H

// maybe can take those includes down (because of commend).
#include <iostream>
#include <queue>
#include <map>
#include <string>
#include <sstream>
#include <fstream>
#include <regex>

#include "Command.h"

#define EOL '\n'

using namespace std;

class ClassMain {
    queue<string> script;
    map<string, double> symbolTable;
    //map<string, Command *> commandTypes;
public:
    void lexer(const char *fileName) {
        string line;
        ifstream file(fileName);
        // checks for failure opening the file.

        if (!file) {
            cout << "ERROR! could not open file : " << fileName << endl;
            return;
        }

        while (getline(file, line)) {
            // saves each line at 'script' vector.
            addLineToVector(line);
        }

        file.close();
    }

    void cleanStartSpaces(string &line) {
        if (isspace(line[0])) {
            while (isspace(*(line.begin()))) {
                line.erase(line.begin());
            }
        }
    }

    void deleteEol(string &line) {
        char endChar = line[line.size() - 1];
        if (endChar == EOL) {
            line.erase(line.size() - 1);
        }
    }

    string getFirstWord(const string &line) {
        int i = 0;
        string buffer;
        while (line[i] != ' ') {
            buffer += line[i];
            ++i;
        }
        return buffer;
    }

// for the lexer function.
    void addLineToVector(string &line) {
        deleteEol(line);
        cleanStartSpaces(line);
        string word = getFirstWord(line);
        // getFirstWord(line);
        if (word == "var") {

        } else if (word == "while") {
            saveCondition(line);
        } else if (word == "if") {
            saveCondition(line);
        } else if (word == "sleep") {
            saveOneArgCommand(line);
        } else if (word == "print") {
            saveOneArgCommand(line);
        } else if (word == "connect") {

        } else if (word == "openDataServer") {

        } else {
            // case of a var ( like x = (x+3)*4 ) or '{'
        }
    }

    void saveOneArgCommand(string line) {
        string exp;
        regex reg("\\w*");
        smatch match;

        script.push(getFirstWord(line));    // saving the command name.

        regex_search(line, match, reg);
        line = match.suffix().str();     // getting the rest of the line.

        reg = regex("[^ ]");
        while (regex_search(line, match, reg)) {
            exp += match.str();
            line = match.suffix().str();
        }
        script.push(exp);
    }

    void saveCondition(string line) {
        string exp;
        regex reg("\\w*");
        smatch match;

        script.push(getFirstWord(line)); // saving 'while' or 'if'

        regex_search(line, match, reg);
        line = match.suffix().str();    //  getting the rest of the line.

        reg = regex("[^ {]");
        // getting the condition expression.
        while (regex_search(line, match, reg)) {
            exp += match.str();
            line = match.suffix().str();
        }
        script.push(exp);
        script.push("{");
    }

    void saveVarCommand(string line) {
        script.push(getFirstWord(line));

        regex reg("\\w*");
        smatch match;
        regex_search(line, match, reg);
        line = match.suffix().str();
        // saving the variable name.
        reg = regex("[^ ]+");
        regex_search(line, match, reg);
        script.push(match.str());
        // saving '='.
        line = match.suffix().str();
        reg = regex("=");
        regex_search(line, match, reg);
        script.push("=");
        line = match.suffix().str();

        reg = regex("bind");
        // saving the 'bind'.
        if (regex_search(line, match, reg)) {
            script.push("bind");
            line = match.suffix().str();
            reg = regex("[^ ]+");
            regex_search(line, match, reg);
            script.push(match.str());
            // else, saving the expression.
        } else {
            string exp;
            reg = regex("[^ ]");
            while (regex_search(line, match, reg)) {
                exp += match.str();
                line = match.suffix().str();
            }
            script.push(exp);
        }
    }

    void saveConnectCommand(string line) {
        script.push(getFirstWord(line));
        regex reg("\\w*");
        smatch match;

        regex_search(line, match, reg);
        line = match.suffix().str();

        reg = regex(R"(\d+.\d+.\d+.\d+)");
        regex_search(line, match, reg);
        line = match.suffix().str();
        script.push(match.str());

        reg = regex("[^ ]");
        string exp;
        while (regex_search(line, match, reg)) {
            exp += match.str();
            line = match.suffix().str();
        }
        script.push(exp);
    }

    void saveServerCommand(string line){
        string first,second,temp;
        //push "OpenDataServer"
        script.push(getFirstWord(line));
        regex reg("\\w*");
        smatch match;

        regex_search(line, match, reg);
        line = match.suffix().str(); //get what after "open..."

        reg = regex(".+[ ]{1}"); //search for digit,space , digit
        regex_search(line,match,reg);
        temp = match.str(); //get first expression (not ready)
        line = match.suffix().str(); //rest of the line(after first word)

        reg = regex("[^ ]");
        //remove all spaces in first expression
        while(regex_search(temp, match, reg)) {
            first += match.str();
            temp = match.suffix().str();
        }
        script.push(first);

        //remove all spaces in the second expression
        while(regex_search(line, match, reg)) {
            second += match.str();
            line = match.suffix().str();
        }
        script.push(second);

    }
};

#endif