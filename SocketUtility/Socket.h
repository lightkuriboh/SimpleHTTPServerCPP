//
// Created by kuribohkute on 14/01/2020.
//

#ifndef DTLMINIPROJECT_SOCKET_H
#define DTLMINIPROJECT_SOCKET_H

#include <cstdio>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "../constants.h"

namespace SocketUtility {
    class Socket {
    private:
        int communicationDomain = AF_INET;
        int communicationType = SOCK_STREAM;
        int socketProtocol = 0;
        int socketOption = 0;
        int activePORT = SocketUtility::PORT;

        ReturnStatus createSocket();
        ReturnStatus socketOptions();
        void setUpAddress(int port);
        ReturnStatus identifySocket();

    protected:
        sockaddr_in address{};
        sockaddr clientAddress{};
        socklen_t addressLength = 0;
        socklen_t clientAddressLength = 0;

        int socketMaster = 0;

        virtual ReturnStatus makeSocketListening() = 0;
        virtual ReturnStatus listeningConnections() = 0;
        virtual void startingSocket() = 0;
        void initSocket(int _communicationDomain, int _communicationType);
    public:
        void start();
        Socket();

    };
}

#endif //DTLMINIPROJECT_SOCKET_H
