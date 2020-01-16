//
// Created by kuribohkute on 14/01/2020.
//

#ifndef DTLMINIPROJECT_TCPSOCKET_H
#define DTLMINIPROJECT_TCPSOCKET_H

#include <map>
#include <vector>
#include <sys/epoll.h>
#include "Socket.h"
#include "../EPollUtility/EPollUtilities.h"
#include "../Server/Server.h"
#include "../utils/Timer.h"
#include "../utils/ThreadPool.h"

namespace SocketUtility {
    class TCPSocket : public Socket {
    private:
        ThreadPool *threadPool = nullptr;
        ServerNS::Server* server;
        std::vector<epoll_event> ePollEvents;
        ReturnStatus makeSocketListening() override;
        ReturnStatus listeningConnections() override;
        void startingSocket() override;
        static void addNewConnection(const int &context, const int &socketfd);
        static void closeConnection(const int &context, const int &socketfd);
    public:
        TCPSocket();
        ~TCPSocket();
        void initServer(ServerNS::Server* _server);
    };
}

#endif //DTLMINIPROJECT_TCPSOCKET_H
