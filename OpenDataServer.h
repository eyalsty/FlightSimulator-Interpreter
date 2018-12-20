

#ifndef PROJECT1_OPENDATASERVER_H
#define PROJECT1_OPENDATASERVER_H


#include "Command.h"

class OpenDataServer : public Command {
private:
public:
    explicit OpenDataServer(queue<string> &_orders) : Command(_orders) {}

    int execute();
};


#endif //PROJECT1_OPENDATASERVER_H
