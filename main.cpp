#include "ClassMain.h"

using namespace std;

int main(int argc, char** argv) {
    try {
        if(argc >= 2) {
            ClassMain main;
            main.parser(argv[1]);
        }
    } catch (const CommandException& e) {
        e.print();
    }
    return 0;
}
