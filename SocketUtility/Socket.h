//
// Created by kuribohkute on 14/01/2020.
//

#ifndef SIMPLECPPSERVER_SOCKET_H
#define SIMPLECPPSERVER_SOCKET_H

#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstdio>
#include <cstring>
#include <iostream>

#include "constants.h"

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

#endif //SIMPLECPPSERVER_SOCKET_H
