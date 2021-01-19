
#include "TCPSocket.h"

#include <unistd.h>

#include <map>

SocketUtility::TCPSocket::TCPSocket(): Socket() {
    this->server = nullptr;
    initSocket(AF_INET, SOCK_STREAM);
    this->ePollEvents.resize(SocketUtility::maximumConnections + 1);
}

ReturnStatus SocketUtility::TCPSocket::makeSocketListening() {
    // tells a socket that it should be capable of accepting incoming connections
    if (listen(this->socketMaster, SocketUtility::maximumPendingConnections) < 0) {
        perror("Listening already");
        return ReturnStatus::FAILURE;
    }
    return ReturnStatus::SUCCESS;
}

ReturnStatus SocketUtility::TCPSocket::listeningConnections() {
    int ePollFDs = epoll_create(SocketUtility::maximumConnections + 1);

    addNewConnection(ePollFDs, this->socketMaster);
    while (true) {
        int numberFDs = epoll_wait(ePollFDs, &*this->ePollEvents.begin(), SocketUtility::maximumConnections, 0);
        for (int i = 0; i < numberFDs; ++i) {
            auto sockfd = this->ePollEvents[i].data.fd;
            if (this->ePollEvents[i].events & EPOLLERR || this->ePollEvents[i].events & EPOLLHUP) {
                close(this->ePollEvents[i].data.fd);
            } else
            if (sockfd == this->socketMaster) {
                int newSocket = accept(this->socketMaster, &this->clientAddress, &this->clientAddressLength);
                if (newSocket < 0) {
                    perror("Accepting!");
                    return ReturnStatus::FAILURE;
                }
                SocketUtility::TCPSocket::addNewConnection(ePollFDs, newSocket);
            } else {
                if (this->ePollEvents[i].events & EPOLLERR   // some errors happened with the file descriptor
                || this->ePollEvents[i].events & EPOLLHUP    // peer had closed its side of the channel
                ) {
                    SocketUtility::TCPSocket::closeConnection(ePollFDs, sockfd);
                } else {
                    this->server->handleRequest(sockfd);
                }
            }
        }
    }
}

void SocketUtility::TCPSocket::startingSocket() {
    if (makeSocketListening() == ReturnStatus::SUCCESS) {
        listeningConnections();
    }
}

void SocketUtility::TCPSocket::closeConnection(const int &context, const int &socketfd) {
    EPollUtility::EPollUtilities::registerToEPoll(context, socketfd, EPOLLERR, EPOLL_CTL_DEL);
    close(socketfd);
}

void SocketUtility::TCPSocket::addNewConnection(const int &context, const int &socketfd) {
    EPollUtility::EPollUtilities::registerToEPoll(context, socketfd, EPOLLIN, EPOLL_CTL_ADD);
}

void SocketUtility::TCPSocket::initServer(std::unique_ptr<ServerNS::Server> _server) {
    this->server = std::move(_server);
}
