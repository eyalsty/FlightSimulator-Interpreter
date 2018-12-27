
#ifndef PROJECT1_OPENDATASERVER_H
#define PROJECT1_OPENDATASERVER_H
#define ARGS_NUM 2
#include "SymbolTable.h"
#include "Command.h"
#include "DataReaderServer.h"

class OpenDataServer : public Command {
private:
    SymbolTable *symbols;
    DataReaderServer *reader;
public:
    OpenDataServer(queue<string> &_orders, SymbolTable *symbols, DataReaderServer *reader) :
            Command(_orders), symbols(symbols), reader(reader) {}

    int execute();

    inline void toStop() {
        this->reader->stop();
    }
    ~OpenDataServer() {
        delete this->reader;
    }

};

#endif //PROJECT1_OPENDATASERVER_H
