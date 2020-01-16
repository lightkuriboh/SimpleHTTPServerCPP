//
// Created by kuribohkute on 15/01/2020.
//

#ifndef DTLMINIPROJECT_MYSERVER_H
#define DTLMINIPROJECT_MYSERVER_H

#include "Server.h"
#include "../SocketUtility/TCPSocket.h"
#include <cstring>
#include "Requests/RESTInformation.h"
#include "Requests/RESTHandler.h"
#include "Requests/RequestHandlers.h"
#include <map>

namespace ServerNS {
    class MyServer : public Server {
    private:
        SocketUtility::TCPSocket* tcpSocket = nullptr;
    public:
        explicit MyServer(bool _onlyPureRequest = false);
        ~MyServer() override;
        void start();
        void handleRequest(const int &sockfd) override;
        static void respondBack(const int &sockfd, std::string &resp);
    };
}

#endif //DTLMINIPROJECT_MYSERVER_H
