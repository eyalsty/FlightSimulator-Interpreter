#ifndef SLEEPCOMMAND_H
#define SLEEPCOMMAND_H

#include "Command.h"
#include "SYalgorithm.h"
#include <chrono>
#include <thread>

#define ARG_NUM 1

class SleepCommand : public Command {
public:
    explicit SleepCommand(queue<string> &_orders) : Command(_orders) {}

    int execute() {
        // getting the time.
        unsigned int time =
                (unsigned int) shuntingYard(orders.back())->calculate();
        // popping this used oreder from the queue.
        orders.pop();
        // sleeping for 'time' milliseconds.
        std::this_thread::sleep_for(std::chrono::milliseconds(time));

        // the number of args that we red.
        return ARG_NUM;
    }
};
#endif
