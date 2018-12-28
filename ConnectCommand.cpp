#include "ConnectCommand.h"

//add new message packet to the queue of the packets
void ConnectCommand::sendMessage(string &p, double v) {
    auto *pack = new MsgPacket;
    pack->path = p;
    pack->value = v;
    this->messages.push(pack);
}

//thread for sending messages to simulator
void *ConnectCommand::thread_func(void *arg) {
    auto *params = (MyParams *) arg;
    ConnectCommand *con = params->connection;
    //open new client to communicate to simulator
    con->openClient(params->IP, params->port);
    delete params; //finished the communication
    return nullptr;
}

//ASSUMING IP IS ON TOP OF QUEUE
int ConnectCommand::execute() {
    int pthread_id;
    this->setIsConnection(true);
    string sIP = this->orders.front(); //get ip from top of queue
    this->orders.pop(); //pop the ip
    string sPort = this->orders.front(); //get port from top of queue
    Expression *exPort = shuntingYard(sPort);
    int portNum = (int) exPort->calculate(); //calculate the port
    this->orders.pop(); //pop port from queue
    struct MyParams *params = new MyParams(); //struct for thread
    params->port = portNum;
    params->IP = sIP;
    params->connection = this;
    //create new thread for communicating with simulator
    pthread_create(&trid, nullptr, ConnectCommand::thread_func, params);
    delete exPort;
    return ARGS_NUM;
}


void ConnectCommand::openClient(string ip, int port) {
    int sockfd, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    /* Create a socket point */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror(OPEN_SOCKET_ERR);
        exit(1);
    }

    server = gethostbyname(ip.c_str());
    if (server == NULL) {
        fprintf(stderr, NO_HOST_ERR);
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(port);

    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror(CONNECT_ERR);
        exit(1);
    }
    cout << SUCCESSFUL_CONNECT << endl;

    /* the client now listening to messages in the messages queue.
     * if its not empty, it will pop the top message and will sent it to the
     * simulator.
    */
    while (!this->shouldStop) {
        if (!this->messages.empty()) { //if there are packets to send
            pthread_mutex_lock(&mutex);
            MsgPacket *curr = messages.front();
            string send = "set " + curr->path + " " + to_string(curr->value) + "\r\n";

            /* Send message to the server */

            n = write(sockfd, send.c_str(), send.size());
            if (n < 0) {
                perror(WRITE_ERR);
                exit(1);
            }
            delete curr;
            messages.pop();
            pthread_mutex_unlock(&mutex);
        }
    }
    close(sockfd);
}
