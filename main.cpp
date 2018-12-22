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
    ClassMain m;
    string s = "var throttle = bind \"controls/throttle/engine\"";
    string s2 = "var roll =  -30-(30 * 80)";
    m.saveVarCommand(s);
    m.saveVarCommand(s2);
    string ss = "3*(-22 / 3 ) 4";
    m.saveServerCommand(ss);
    cout << "asdasd" << endl;
    return 0;
}