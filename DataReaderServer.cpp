#include <iostream>
#include "DataReaderServer.h"


void DataReaderServer::openServer(int port, int HZ) {
    struct MyParams *params = new MyParams();
    params->port = port;
    params->hz = HZ;
    params->reader = this;
    pthread_create(&trid, nullptr, thread_func, params);
}

void *DataReaderServer::thread_func(void *arg) {
    struct MyParams *params = (struct MyParams *) arg;
    struct sockaddr_in serv_addr, cli_addr;
    string s;
    char buffer[1];
    int sockfd, newsockfd, portno, clilen;
    int n;

    /* First call to socket() function */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    /* Initialize socket structure */
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = params->port;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    /* Now bind the host address using bind() call.*/
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        exit(1);
    }

    /* Now start listening for the clients, here process will
       * go in sleep mode and will wait for the incoming connection
    */

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    /* Accept actual connection from the client */
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t *) &clilen);

    if (newsockfd < 0) {
        perror("ERROR on accept");
        exit(1);
    }

    params->reader->setIsConnection(true);
    cout << "Server's connection established\n";

    /* If connection is established then start communicating */
    while (!params->reader->toStop) {
        //read all 23 (until \n) values from simulator into s
        n = read(newsockfd, buffer, 1);
        while (buffer[0] != '\n') {
            if (n < 0) {
                perror("ERROR reading from socket");
                exit(1);
            }
            s += buffer[0];
            n = read(newsockfd, buffer, 1);
        }
        cout << s << endl;

        params->reader->updateSymbolTable(s);
        s = "";
        sleep(params->hz / MIL_SEC);
    }
    close(newsockfd);
    delete params;
    return nullptr;
}

void DataReaderServer::updateSymbolTable(string &values) {
    string allPath[MAX_VARS] = {INDICATE_SPEED, INDICATE_ALT,
                                PRESSURE_ALT, PITCH_DEG,
                                ROLL_DEG, IN_PITCH_DEG,
                                IN_ROLL_DEG,
                                ENC_INDICATE_ALT,
                                ENC_PRESURE_ALT, GPS_ALT,
                                GPS_GRND_SPD, GPS_VERTICAL_SPD,
                                HEAD_DEG, CMPS_HEAD_DEG,
                                SLIP_SKID, TURN_RATE, SPEED_FPM,
                                AILERON, ELEVATOR, RUDDER,
                                FLAPS, THROTTLE, RPM};
    istringstream ss(values);
    char splitChar = ',';
    vector<double> tokens;

    for (string value; getline(ss, value, splitChar); tokens.push_back(stod(value)));

    pthread_mutex_lock(&mutex);
    for (int i = 0; i < MAX_VARS; ++i) {
        if (!tokens.empty()) {
            this->symbols->updateFromSimulator(tokens[i], allPath[i]);

        }
    }
    pthread_mutex_unlock(&mutex);
}


