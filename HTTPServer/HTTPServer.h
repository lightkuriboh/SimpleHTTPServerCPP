
#ifndef SIMPLECPPSERVER_HTTPSERVER_H
#define SIMPLECPPSERVER_HTTPSERVER_H

#include <sys/epoll.h>

#include <memory>
#include <vector>

#include "ApplicationServer/ApplicationServer.h"
#include "HTTPServer/TCPSocket.h"

namespace SimpleHTTPServer {
    class HTTPServer {
    private:
        std::unique_ptr<TCPSocket> myTcpSocket;
        std::vector<epoll_event> epollEvents;
        SimpleHTTPServer::ApplicationServer server = SimpleHTTPServer::ApplicationServer();
        int epollContext = 0;
        void addNewConnection(const int &socketFileDescriptor) const;
        void closeConnection(const int &socketFileDescriptor) const;

        [[nodiscard]] bool isSocketMaster(const int &socketFileDescriptor) const {
            return socketFileDescriptor == this->myTcpSocket->getSocketMaster();
        }
    public:
        ReturnStatus listeningConnections();

        HTTPServer();
        void start();
    };
}

#endif //SIMPLECPPSERVER_HTTPSERVER_H
