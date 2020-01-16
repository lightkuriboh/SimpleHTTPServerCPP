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
        explicit MyServer(bool _onlyPureRequest = false, bool _cleanTerminatedConnections = true);
        ~MyServer() override;
        void start();
        ReturnStatus handleRequest(const int &sockfd) override;
        ReturnStatus writingResponse(const int &sockfd, const int &context, void (*callback)(const int&, const int&)) override;
    };
}

#endif //DTLMINIPROJECT_MYSERVER_H
