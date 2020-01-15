//
// Created by kuribohkute on 15/01/2020.
//

#ifndef DTLMINIPROJECT_MYSERVER_H
#define DTLMINIPROJECT_MYSERVER_H

#include "Server.h"
#include "../SocketUtility/TCPSocket.h"
#include <cstring>
#include <map>

namespace Server {
    class MyServer : public Server {
    private:
        std::map<int, std::string> responses;
        SocketUtility::TCPSocket* tcpSocket = nullptr;
    public:
        MyServer();
        ~MyServer() override;
        void start();
        ReturnStatus handleRequest(int sockfd) override;
        ReturnStatus writingResponse(int sockfd, int context, void (*callback)(int, int)) override;
    };
}

#endif //DTLMINIPROJECT_MYSERVER_H
