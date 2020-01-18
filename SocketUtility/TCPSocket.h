//
// Created by kuribohkute on 14/01/2020.
//

#ifndef DTLMINIPROJECT_TCPSOCKET_H
#define DTLMINIPROJECT_TCPSOCKET_H

#include <map>
#include <vector>
#include "Socket.h"
#include <sys/epoll.h>

#include "../Server/Server.h"
#include "../EPollUtility/EPollUtilities.h"

namespace SocketUtility {
    class TCPSocket : public Socket {
    private:
        ServerNS::Server* server;
        std::vector<epoll_event> ePollEvents;
        ReturnStatus makeSocketListening() override;
        ReturnStatus listeningConnections() override;
        void startingSocket() override;
        static void addNewConnection(const int &context, const int &socketfd);
        static void closeConnection(const int &context, const int &socketfd);
    public:
        TCPSocket();
        void initServer(ServerNS::Server* _server);
    };
}

#endif //DTLMINIPROJECT_TCPSOCKET_H
