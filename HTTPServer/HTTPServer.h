
#ifndef SIMPLECPPSERVER_HTTPSERVER_H
#define SIMPLECPPSERVER_HTTPSERVER_H

#include <sys/epoll.h>

#include <vector>

#include "ApplicationServer/ApplicationServer.h"
#include "HTTPServer/TCPSocket.h"
#include "utils/ConfigParser.h"

namespace SimpleHTTPServer {
    class HTTPServer {
    private:
        Utils::Config config = Utils::Config();
        TCPSocket myTcpSocket = SimpleHTTPServer::TCPSocket();
        SimpleHTTPServer::ApplicationServer server = SimpleHTTPServer::ApplicationServer(config);

        std::vector<epoll_event> epollEvents;
        int epollContext = 0;

        void addNewConnection(const int &socketFileDescriptor) const;
        void closeConnection(const int &socketFileDescriptor) const;

        [[nodiscard]] bool isSocketMaster(const int &socketFileDescriptor) const {
            return socketFileDescriptor == this->myTcpSocket.getSocketMaster();
        }
    public:
        ReturnStatus listeningConnections();

        HTTPServer();
        void start();
    };
}

#endif //SIMPLECPPSERVER_HTTPSERVER_H
