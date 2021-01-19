
#ifndef SIMPLECPPSERVER_TCPSOCKET_H
#define SIMPLECPPSERVER_TCPSOCKET_H

#include <sys/epoll.h>

#include <memory>
#include <vector>

#include "libs/EPollUtility.h"
#include "Server/Server.h"
#include "Socket.h"

namespace SimpleHTTPServer {
    class TCPSocket : public Socket {
    private:
        std::unique_ptr<SimpleHTTPServer::Server> server = nullptr;
        std::vector<epoll_event> ePollEvents;
        ReturnStatus makeSocketListening() override;
        ReturnStatus listeningConnections() override;
        void startingSocket() override;
        static void addNewConnection(const int &context, const int &socketFileDescriptor);
        static void closeConnection(const int &context, const int &socketFileDescriptor);
    public:
        TCPSocket();
        void initServer(std::unique_ptr<SimpleHTTPServer::Server> _server);
    };
}

#endif //SIMPLECPPSERVER_TCPSOCKET_H
