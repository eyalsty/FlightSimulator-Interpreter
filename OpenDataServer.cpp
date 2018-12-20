#include <pthread.h>

#include "OpenDataServer.h"

int OpenDataServer::execute() {
    pthread_t trid;
    unsigned int port =
            (unsigned int) shuntingYard(this->orders.front())->calculate();

}