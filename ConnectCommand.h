#ifndef PROJECT1_CONNECTCOMMAND_H
#define PROJECT1_CONNECTCOMMAND_H
#define ARGS_NUM 2
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include "Expression.h"
#include "Command.h"

using namespace std;

class ConnectCommand: public Command {
private:
    string msg;
    bool toSend = false;
public:
    explicit ConnectCommand(queue<string>  &_orders): Command(_orders) {};
    struct MyParams
    {
        string IP;
        int port;
        ConnectCommand *connection;
    };
    int execute();
    void openClient(string ip, int port);
    static void* thread_func(void* arg);
    void setMembers(bool send, string msg);

};


#endif //PROJECT1_CONNECTCOMMAND_H
