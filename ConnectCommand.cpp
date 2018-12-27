
#include "ConnectCommand.h"

void ConnectCommand::sendMessage(string p, double v){
    MsgPacket *pack = new MsgPacket;
    pack->path = p;
    pack->value = v;
    this->messages.push(pack);
}

//thread for sending messages to simulator
void *ConnectCommand::thread_func(void *arg) {
    struct MyParams *params = (struct MyParams *) arg;
    ConnectCommand *con = params->connection;
    //open new client to communicate to simulator
    con->openClient(params->IP, params->port);
    delete params; //finished the communication
    return nullptr;
}

//ASSUMING IP IS ON TOP OF QUEUE
int ConnectCommand::execute() {
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
    pthread_t trid; //create new thread for communicating with simulator
    pthread_create(&trid, nullptr, ConnectCommand::thread_func, params);
    //delete exPort;
    return ARGS_NUM;
}


void ConnectCommand::openClient(string ip, int port) {
    int sockfd, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    /* Create a socket point */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    server = gethostbyname(ip.c_str());
    if (server == NULL) {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(port);


    while (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        //perror("ERROR connecting");
        //exit(1);
        cout << "WAITING !" << endl;
    }
    cout << "succesfully connected to the plane !" << endl;

    /* the client will start waiting for messages to be sent to the simulator,
     * if message is "quit" we will stop.
    */
    while (!this->shouldStop) {
        if (!this->messages.empty()) { //if there are packets to send
            pthread_mutex_lock(&mutex);
            MsgPacket *curr = messages.front();
            string send = "set " + curr->path + " " + to_string(curr->value) + "\r\n";
            /* Send message to the server */

            n = write(sockfd, send.c_str(), send.size());
            if (n < 0) {
                perror("ERROR writing to socket");
                exit(1);
            }
            cout << "sent:  " << send << endl; //indication for us to see the message sent
            delete curr;
            messages.pop();
            pthread_mutex_unlock(&mutex);
        }
    }
    close(sockfd);
}
