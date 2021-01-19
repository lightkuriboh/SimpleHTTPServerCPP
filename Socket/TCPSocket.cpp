
#include "TCPSocket.h"

#include <unistd.h>

#include <map>

SimpleHTTPServer::TCPSocket::TCPSocket(): Socket() {
    this->server = nullptr;
    initSocket(AF_INET, SOCK_STREAM);
    this->ePollEvents.resize(SimpleHTTPServer::maximumConnections + 1);
}

ReturnStatus SimpleHTTPServer::TCPSocket::makeSocketListening() {
    // tells a socket that it should be capable of accepting incoming connections
    if (listen(this->socketMaster, SimpleHTTPServer::maximumPendingConnections) < 0) {
        perror("Listening already");
        return ReturnStatus::FAILURE;
    }
    return ReturnStatus::SUCCESS;
}

ReturnStatus SimpleHTTPServer::TCPSocket::listeningConnections() {
    int ePollFDs = epoll_create(SimpleHTTPServer::maximumConnections + 1);

    addNewConnection(ePollFDs, this->socketMaster);
    while (true) {
        int numberFDs = epoll_wait(ePollFDs, &*this->ePollEvents.begin(), SimpleHTTPServer::maximumConnections, 0);
        for (int i = 0; i < numberFDs; ++i) {
            auto socketFileDescriptor = this->ePollEvents[i].data.fd;
            if (this->ePollEvents[i].events & EPOLLERR || this->ePollEvents[i].events & EPOLLHUP) {
                close(this->ePollEvents[i].data.fd);
            } else
            if (socketFileDescriptor == this->socketMaster) {
                int newSocket = accept(this->socketMaster, &this->clientAddress, &this->clientAddressLength);
                if (newSocket < 0) {
                    perror("Accepting!");
                    return ReturnStatus::FAILURE;
                }
                SimpleHTTPServer::TCPSocket::addNewConnection(ePollFDs, newSocket);
            } else {
                if (this->ePollEvents[i].events & EPOLLERR   // some errors happened with the file descriptor
                || this->ePollEvents[i].events & EPOLLHUP    // peer had closed its side of the channel
                ) {
                    SimpleHTTPServer::TCPSocket::closeConnection(ePollFDs, socketFileDescriptor);
                } else {
                    this->server->handleRequest(socketFileDescriptor);
                }
            }
        }
    }
}

void SimpleHTTPServer::TCPSocket::startingSocket() {
    if (makeSocketListening() == ReturnStatus::SUCCESS) {
        listeningConnections();
    }
}

void SimpleHTTPServer::TCPSocket::closeConnection(const int &context, const int &socketFileDescriptor) {
    LibraryWrapper::EPoll::removeFromEpoll(context, socketFileDescriptor);
    close(socketFileDescriptor);
}

void SimpleHTTPServer::TCPSocket::addNewConnection(const int &context, const int &socketFileDescriptor) {
    LibraryWrapper::EPoll::addToEpoll(context, socketFileDescriptor);
}

void SimpleHTTPServer::TCPSocket::initServer(std::unique_ptr<SimpleHTTPServer::Server> _server) {
    this->server = std::move(_server);
}
