#include "MainClass.h"

void MainClass::lexer(const char *fileName) {
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

// for the lexer function.
void MainClass::addLineToVector(string &line) {
    string word;
    istringstream iss;
    char endChar = line[line.size() - 1];

    // case which the last char is '\n'.
    if (endChar == EOL) {
        line.erase(line.size() - 1);
    } else if (isspace(line[0])) {
        // deletes white spaces from the start of the text.
        while (isspace(*(line.begin()))) {
            line.erase(line.begin());
        }
    }

    iss.str(line);
    // saves the words of line in 'script', without spaces.
    while (getline(iss, word, ' ')) {
        script.push_back(word);
    }
}