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
    x.push("from the printCommandExecute");
    try{
    Command* c = new PrintCommand(x);
    c->execute();
    } catch (const CommandException& e){
        e.print();
    }
    cout << "hello, world!" << endl;
    return 0;
}