//
// Created by kuribohkute on 14/01/2020.
//

#ifndef DTLMINIPROJECT_TCPSOCKET_H
#define DTLMINIPROJECT_TCPSOCKET_H

#include <vector>
#include <sys/epoll.h>
#include "Socket.h"
#include "../EPollUtility/EPollUtilities.h"
#include "../Server/Server.h"

namespace SocketUtility {
    class TCPSocket : public Socket {
    private:
        Server::Server* server;
        std::vector<epoll_event> ePollEvents;
        ReturnStatus makeSocketListening() override;
        ReturnStatus listeningConnections() override;
        void startingSocket() override;
        static void readyForReadConnection(int context, int socketfd);
        static void readyForWriteConnection(int context, int socketfd);
        void addNewConnection(int context, int socketfd);
        void closeConnection(int context, int socketfd);
    public:
        TCPSocket();
        ~TCPSocket();
        void initServer(Server::Server* _server);
    };
}

#endif //DTLMINIPROJECT_TCPSOCKET_H
