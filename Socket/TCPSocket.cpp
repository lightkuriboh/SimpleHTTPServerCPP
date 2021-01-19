
#include "TCPSocket.h"

#include <unistd.h>

#include <map>

SimpleCPPServer::TCPSocket::TCPSocket(): Socket() {
    this->server = nullptr;
    initSocket(AF_INET, SOCK_STREAM);
    this->ePollEvents.resize(SimpleCPPServer::maximumConnections + 1);
}

ReturnStatus SimpleCPPServer::TCPSocket::makeSocketListening() {
    // tells a socket that it should be capable of accepting incoming connections
    if (listen(this->socketMaster, SimpleCPPServer::maximumPendingConnections) < 0) {
        perror("Listening already");
        return ReturnStatus::FAILURE;
    }
    return ReturnStatus::SUCCESS;
}

ReturnStatus SimpleCPPServer::TCPSocket::listeningConnections() {
    int ePollFDs = epoll_create(SimpleCPPServer::maximumConnections + 1);

    addNewConnection(ePollFDs, this->socketMaster);
    while (true) {
        int numberFDs = epoll_wait(ePollFDs, &*this->ePollEvents.begin(), SimpleCPPServer::maximumConnections, 0);
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
                SimpleCPPServer::TCPSocket::addNewConnection(ePollFDs, newSocket);
            } else {
                if (this->ePollEvents[i].events & EPOLLERR   // some errors happened with the file descriptor
                || this->ePollEvents[i].events & EPOLLHUP    // peer had closed its side of the channel
                ) {
                    SimpleCPPServer::TCPSocket::closeConnection(ePollFDs, socketFileDescriptor);
                } else {
                    this->server->handleRequest(socketFileDescriptor);
                }
            }
        }
    }
}

void SimpleCPPServer::TCPSocket::startingSocket() {
    if (makeSocketListening() == ReturnStatus::SUCCESS) {
        listeningConnections();
    }
}

void SimpleCPPServer::TCPSocket::closeConnection(const int &context, const int &socketFileDescriptor) {
    LibraryWrapper::EPoll::removeFromEpoll(context, socketFileDescriptor);
    close(socketFileDescriptor);
}

void SimpleCPPServer::TCPSocket::addNewConnection(const int &context, const int &socketFileDescriptor) {
    LibraryWrapper::EPoll::addToEpoll(context, socketFileDescriptor);
}

void SimpleCPPServer::TCPSocket::initServer(std::unique_ptr<SimpleCPPServer::Server> _server) {
    this->server = std::move(_server);
}
