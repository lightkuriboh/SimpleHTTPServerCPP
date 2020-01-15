//
// Created by kuribohkute on 14/01/2020.
//
#include "TCPSocket.h"

SocketUtility::TCPSocket::TCPSocket() {
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

    std::string hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";

    int ePollFDs = epoll_create(SocketUtility::maximumConnections + 1);
    addNewConnection(ePollFDs, this->socketMaster);

    while (true) {
        int numberFDs = epoll_wait(ePollFDs, &*this->ePollEvents.begin(), SocketUtility::maximumConnections, 0);
        for (int i = 0; i < numberFDs; ++i) {
            auto sockfd = this->ePollEvents[i].data.fd;
            // New connection
            if (sockfd == this->socketMaster) {
                int newSocket = accept(this->socketMaster, (sockaddr *) this->address, (socklen_t *) &this->addressLength);
                if (newSocket < 0) {
                    perror("Accepting!");
                    return ReturnStatus::FAILURE;
                }
                SocketUtility::TCPSocket::addNewConnection(ePollFDs, newSocket);
            } else {
                // Ready to read data
                if (this->ePollEvents[i].events & EPOLLIN) {
                    if (this->server->handleRequest(sockfd) == ReturnStatus::FAILURE) {
                        SocketUtility::TCPSocket::closeConnection(ePollFDs, sockfd);
                    } else {
                        write(sockfd, &*hello.begin(), strlen(&*hello.begin()));
                        SocketUtility::TCPSocket::readyForWriteConnection(ePollFDs, ePollEvents[i].data.fd);
                    }
                } else {
                    // Data is ready to be sent
                    if (this->ePollEvents[i].events & EPOLLOUT) {
                        if (this->server->writingResponse(sockfd, ePollFDs, SocketUtility::TCPSocket::readyForReadConnection) == ReturnStatus::FAILURE) {
                            SocketUtility::TCPSocket::closeConnection(ePollFDs, sockfd);
                        }
                    }
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

void SocketUtility::TCPSocket::closeConnection(int context, int socketfd) {
    EPollUtility::EPollUtilities::registerToEPoll(context, socketfd, EPOLLET, EPOLL_CTL_DEL);
    close(socketfd);
}

void SocketUtility::TCPSocket::readyForReadConnection(int context, int socketfd) {
    EPollUtility::EPollUtilities::registerToEPoll(context, socketfd, EPOLLIN, EPOLL_CTL_MOD);
}

void SocketUtility::TCPSocket::readyForWriteConnection(int context, int socketfd) {
    EPollUtility::EPollUtilities::registerToEPoll(context, socketfd, EPOLLOUT, EPOLL_CTL_MOD);
}

void SocketUtility::TCPSocket::addNewConnection(int context, int socketfd) {
    EPollUtility::EPollUtilities::registerToEPoll(context, socketfd, EPOLLIN, EPOLL_CTL_ADD);
}

void SocketUtility::TCPSocket::initServer(Server::Server *_server) {
    this->server = _server;
}

SocketUtility::TCPSocket::~TCPSocket() {
    delete this->server;
}
