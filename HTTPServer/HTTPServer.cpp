
#include "HTTPServer/HTTPServer.h"

#include <unistd.h>

#include <map>

#include <libs/EPollUtility.h>

ReturnStatus SimpleHTTPServer::HTTPServer::listeningConnections() {
    int ePollFDs = epoll_create(SimpleHTTPServer::maximumConnections + 1);

    addNewConnection(ePollFDs, this->myTcpSocket->getSocketMaster());
    while (true) {
        int numberFDs = epoll_wait(ePollFDs, &*this->ePollEvents.begin(), SimpleHTTPServer::maximumConnections, 0);
        for (int i = 0; i < numberFDs; ++i) {
            auto socketFileDescriptor = this->ePollEvents[i].data.fd;
            if (socketFileDescriptor == this->myTcpSocket->getSocketMaster()) {
                sockaddr clientAddress{};
                socklen_t clientAddressLength = sizeof(clientAddress);
                int newSocket = accept(this->myTcpSocket->getSocketMaster(), &clientAddress, &clientAddressLength);

                if (newSocket < 0) {
                    perror("Accepting!");
                    return ReturnStatus::FAILURE;
                }
                SimpleHTTPServer::HTTPServer::addNewConnection(ePollFDs, newSocket);
            } else {
                if (this->ePollEvents[i].events & EPOLLERR   // some errors happened with the file descriptor
                    || this->ePollEvents[i].events & EPOLLHUP    // peer had closed its side of the channel
                        ) {
                    SimpleHTTPServer::HTTPServer::closeConnection(ePollFDs, socketFileDescriptor);
                } else {
                    this->server.handleRequest(socketFileDescriptor);
                }
            }
        }
    }
}

void SimpleHTTPServer::HTTPServer::closeConnection(const int &context, const int &socketFileDescriptor) {
    LibraryWrapper::EPoll::removeFromEpoll(context, socketFileDescriptor);
    close(socketFileDescriptor);
}

void SimpleHTTPServer::HTTPServer::addNewConnection(const int &context, const int &socketFileDescriptor) {
    LibraryWrapper::EPoll::addToEpoll(context, socketFileDescriptor);
}

SimpleHTTPServer::HTTPServer::HTTPServer() {
    this->myTcpSocket = std::make_unique<TCPSocket>();
    this->ePollEvents.resize(SimpleHTTPServer::maximumConnections + 1);
}

void SimpleHTTPServer::HTTPServer::start() {
    this->listeningConnections();
}
