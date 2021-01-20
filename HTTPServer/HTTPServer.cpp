
#include "HTTPServer/HTTPServer.h"

#include <unistd.h>

#include <map>

#include <libs/EPollUtility.h>

ReturnStatus SimpleHTTPServer::HTTPServer::listeningConnections() {
    addNewConnection(this->myTcpSocket->getSocketMaster());
    while (true) {
        int numberFDs = LibraryWrapper::EPoll::getChangedEPollEvents(this->epollContext, this->epollEvents);
        for (int i = 0; i < numberFDs; ++i) {
            auto socketFileDescriptor = this->epollEvents[i].data.fd;
            if (this->isSocketMaster(socketFileDescriptor)) {
                sockaddr clientAddress{};
                socklen_t clientAddressLength = sizeof(clientAddress);
                int newSocket = accept(this->myTcpSocket->getSocketMaster(), &clientAddress, &clientAddressLength);

                if (newSocket < 0) {
                    perror("Accepting!");
                    return ReturnStatus::FAILURE;
                }
                SimpleHTTPServer::HTTPServer::addNewConnection(newSocket);
            } else {
                if (LibraryWrapper::EPoll::errorOccurredWithEPollEvent(this->epollEvents[i])
                    || LibraryWrapper::EPoll::clientClosedTheConnection(this->epollEvents[i])) {
                    SimpleHTTPServer::HTTPServer::closeConnection(socketFileDescriptor);
                } else {
                    this->server.handleRequest(socketFileDescriptor);
                }
            }
        }
    }
}

void SimpleHTTPServer::HTTPServer::closeConnection(const int &socketFileDescriptor) const {
    LibraryWrapper::EPoll::removeFromEpoll(this->epollContext, socketFileDescriptor);
    close(socketFileDescriptor);
}

void SimpleHTTPServer::HTTPServer::addNewConnection(const int &socketFileDescriptor) const {
    LibraryWrapper::EPoll::addToEpoll(this->epollContext, socketFileDescriptor);
}

SimpleHTTPServer::HTTPServer::HTTPServer() {
    this->myTcpSocket = std::make_unique<TCPSocket>();
    this->epollEvents.resize(SimpleHTTPServer::maximumConnections + 1);
    this->epollContext = epoll_create(SimpleHTTPServer::maximumConnections + 1);
}

void SimpleHTTPServer::HTTPServer::start() {
    this->listeningConnections();
}
