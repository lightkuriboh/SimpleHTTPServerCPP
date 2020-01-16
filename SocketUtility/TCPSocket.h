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

namespace SocketUtility {
    class TCPSocket : public Socket {
    private:
        long timeOut = 2000;
        long closeConnectionsDuration = 5000;
        long milestoneTime;
        std::map<int, long> socketTimeOut;
        void scanTerminatedConnections(const int &ePollContext);
        bool cleanTerminatedConnections = false;
        long timer;

        Server::Server* server;
        std::vector<epoll_event> ePollEvents;
        ReturnStatus makeSocketListening() override;
        ReturnStatus listeningConnections() override;
        void startingSocket() override;
        static void readyForReadConnection(const int &context, const int &socketfd);
        static void readyForWriteConnection(const int &context, const int &socketfd);
        void addNewConnection(const int &context, const int &socketfd);
        static void closeConnection(const int &context, const int &socketfd);
    public:
        explicit TCPSocket(bool _cleanTerminatedConnections = true);
        ~TCPSocket();
        void initServer(Server::Server* _server);
    };
}

#endif //DTLMINIPROJECT_TCPSOCKET_H
