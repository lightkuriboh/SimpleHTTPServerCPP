//
// Created by kuribohkute on 14/01/2020.
//

#ifndef DTLMINIPROJECT_SOCKET_H
#define DTLMINIPROJECT_SOCKET_H

#include <iostream>
#include <cstring>
#include <cstdio>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
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
        sockaddr_in* address = nullptr;
        int addressLength = 0;

        int socketMaster = 0;

        virtual ReturnStatus makeSocketListening() = 0;
        virtual ReturnStatus listeningConnections() = 0;
        virtual void startingSocket() = 0;
        void initSocket(int _communicationDomain, int _communicationType);
    public:
        void start();

    };
}

#endif //DTLMINIPROJECT_SOCKET_H
