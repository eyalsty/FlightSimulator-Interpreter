#include "Command.h"
#include "ClassMain.h"
#include "SYalgorithm.h"
#include "SleepCommand.h"
#include "PrintCommand.h"
#include "IfCommand.h"
#include "WhileCommand.h"

#include <stack>
#include <queue>
#include <deque>

using namespace std;

int main() {
    const char* fileName = "checking.txt";
    ClassMain main;
    main.parser(fileName);
    return 0;
}