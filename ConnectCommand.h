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

struct MsgPacket {
    string path;
    double value;
};

class ConnectCommand : public Command {
private:
    bool isConnection = true;
    pthread_mutex_t mutex;
    queue<MsgPacket*> messages;
    bool shouldStop = false;
public:
    ConnectCommand(queue<string> &_orders, pthread_mutex_t m) : Command(_orders), mutex(m){};

    struct MyParams {
        string IP;
        int port;
        ConnectCommand *connection;
    };

    int execute();

    void stop() {
        this->shouldStop = true;
    }

    void openClient(string ip, int port);

    static void *thread_func(void *arg);

    void sendMessage(string p,double v);

    void setIsConnection(bool sign) {
        this->isConnection = sign;
    }

    bool getIsConnection() {
        return this->isConnection;
    }

    ~ConnectCommand() {
        while(!this->messages.empty()) {
            delete messages.front();
        }
    }
};


#endif //PROJECT1_CONNECTCOMMAND_H
