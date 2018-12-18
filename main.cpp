#include "Command.h"
#include "DefineVarCommand.h"
#include "MainClass.h"
#include "SYalgorithm.h"
#include "SleepCommand.h"

#include <stack>
#include <queue>
#include <deque>

using namespace std;

int main() {
    queue<string> x;
    x.push("sleep");
    x.push("1000");
    Command* c = new SleepCommand(x);
    cout << "hello," << endl;
    c->execute();
    x.push("check123");
    cout << "world!" << endl;
    return 0;
}