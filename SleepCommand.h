#ifndef SLEEPCOMMAND_H
#define SLEEPCOMMAND_H

#include "Command.h"
#include <unistd.h>

#define ARG_NUM 1

class SleepCommand : public Command{
public:
    int execute(const vector<string> &v){
        // need to check if the parameter is correct!!@@!@!

        unsigned int time;
        // assuming v starts from the first parameter.
        istringstream(v[0]) >> time;
        usleep(time);

        return ARG_NUM;
    }
};


#endif
