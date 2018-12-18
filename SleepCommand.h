#ifndef SLEEPCOMMAND_H
#define SLEEPCOMMAND_H

#include <chrono>
#include <thread>

#include "Command.h"

#define ARG_NUM 1

class SleepCommand : public Command {
public:
    explicit SleepCommand(queue<string> &_orders) : Command(_orders) {}

    int execute() {
        if(!orders.empty()) {
            // getting the time.
            unsigned int time =
                    (unsigned int) shuntingYard(orders.front())->calculate();
            // popping this used oreder from the queue.
            orders.pop();
            // sleeping for 'time' milliseconds.
            std::this_thread::sleep_for(std::chrono::milliseconds(time));

            // the number of args that we red.
            return ARG_NUM;
        } else {
            throw CommandException("sleep");
        }
    }
};
#endif
