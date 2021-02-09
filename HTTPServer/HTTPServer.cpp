
#include "HTTPServer/HTTPServer.h"

#include <libs/EPollUtility.h>
#include <libs/SocketUtility.h>
#include <libs/UnixStandardUtility.h>

ReturnStatus SimpleHTTPServer::HTTPServer::listeningConnections() {
    this->addNewConnection(this->myTcpSocket.getSocketMaster());
    while (true) {
        int numberFDs = LibraryWrapper::EPoll::getChangedEPollEvents(this->epollContext, this->epollEvents);
        for (int i = 0; i < numberFDs; ++i) {
            auto socketFileDescriptor = this->epollEvents[i].data.fd;
            if (this->isSocketMaster(socketFileDescriptor)) {
                int newSocket = LibraryWrapper::Socket::acceptNewConnection(
                this->myTcpSocket.getSocketMaster()
                );

                if (LibraryWrapper::Socket::createSocketSuccessfully(newSocket)) {
                    this->addNewConnection(newSocket);
                } else {
                    perror("Error accepting new connection!");
                    return ReturnStatus::FAILURE;
                }
            } else {
                if (LibraryWrapper::EPoll::errorOccurredWithEPollEvent(this->epollEvents[i])
                    ||
                    LibraryWrapper::EPoll::clientClosedTheConnection(this->epollEvents[i])) {

                    this->closeConnection(socketFileDescriptor);
                } else {
                    this->server.handleRequest(socketFileDescriptor);
                }
            }
        }
    }
}

void SimpleHTTPServer::HTTPServer::closeConnection(const int &socketFileDescriptor) const {
    LibraryWrapper::EPoll::removeFromEpoll(this->epollContext, socketFileDescriptor);
    LibraryWrapper::UnixStandard::closeFileDescriptor(socketFileDescriptor);
}

void SimpleHTTPServer::HTTPServer::addNewConnection(const int &socketFileDescriptor) const {
    LibraryWrapper::EPoll::addToEpoll(this->epollContext, socketFileDescriptor);
}

SimpleHTTPServer::HTTPServer::HTTPServer() {
    this->epollEvents.resize(this->config.getMaximumConnections() + 1);
    this->epollContext = LibraryWrapper::EPoll::creatEPollContext(this->config.getMaximumConnections() + 1);
}

void SimpleHTTPServer::HTTPServer::start() {
    this->listeningConnections();
}
