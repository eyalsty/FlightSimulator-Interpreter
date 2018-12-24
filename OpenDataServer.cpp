
#include "OpenDataServer.h"

int OpenDataServer::execute() {
    string sPort = this->orders.front();
    this->orders.pop();

    Expression *exPort = shuntingYard(sPort);
    int portNum = (int) exPort->calculate();
    delete (exPort);

    string sHZ = this->orders.front();
    this->orders.pop();

    Expression *exHZ = shuntingYard(sHZ);
    int HZ = (int) exHZ->calculate();
    delete (exHZ);

    this->reader->openServer(portNum, HZ);
    return (int)ARGS_NUM;
}