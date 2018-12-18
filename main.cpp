#include "Command.h"
#include "MainClass.h"
#include "SYalgorithm.h"
#include "SleepCommand.h"
#include "PrintCommand.h"

#include <stack>
#include <queue>
#include <deque>

using namespace std;

int main() {
    queue<string> x;
    //x.push("from the printCommandExecute");
    Command* c = new PrintCommand(x);
    c->execute();
    cout << "hello, world!" << endl;
    return 0;
}