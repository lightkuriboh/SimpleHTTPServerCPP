
#ifndef SIMPLECPPSERVER_HTTPSERVER_H
#define SIMPLECPPSERVER_HTTPSERVER_H

#include <sys/epoll.h>

#include <memory>
#include <vector>

#include "ApplicationServer/MyServer.h"
#include "HTTPServer/TCPSocket.h"

namespace SimpleHTTPServer {
    class HTTPServer {
    private:
        std::unique_ptr<TCPSocket> myTcpSocket;
        std::vector<epoll_event> ePollEvents;
        SimpleHTTPServer::MyServer server = SimpleHTTPServer::MyServer();
    public:
        ReturnStatus listeningConnections();

        HTTPServer();
        void start();

        static void addNewConnection(const int &context, const int &socketFileDescriptor);
        static void closeConnection(const int &context, const int &socketFileDescriptor);
    };
}

#endif //SIMPLECPPSERVER_HTTPSERVER_H
