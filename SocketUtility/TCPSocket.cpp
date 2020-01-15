//
// Created by kuribohkute on 14/01/2020.
//
#include "TCPSocket.h"

SocketUtility::TCPSocket::TCPSocket() {
    initSocket(AF_INET, SOCK_STREAM);
    ePollEvents.resize(SocketUtility::maximumConnections + 1);
}

ReturnStatus SocketUtility::TCPSocket::makeSocketListening() {
    // tells a socket that it should be capable of accepting incoming connections
    if (listen(socketMaster, SocketUtility::maximumPendingConnections) < 0) {
        perror("Listening already");
        return ReturnStatus::FAILURE;
    }
    return ReturnStatus::SUCCESS;
}

ReturnStatus SocketUtility::TCPSocket::listeningConnections() {

    char const *hello = "Hello world!";

    int ePollFDs = epoll_create(SocketUtility::maximumConnections + 1);
    addNewConnection(ePollFDs, socketMaster);

    while (true) {
        int numberFDs = epoll_wait(ePollFDs, &*ePollEvents.begin(), SocketUtility::maximumConnections, 0);
        for (int i = 0; i < numberFDs; ++i) {
            // New connection
            if (ePollEvents[i].data.fd == socketMaster) {
                int newSocket = accept(socketMaster, (sockaddr *) address, (socklen_t *) &addressLength);
                if (newSocket < 0) {
                    perror("Accepting!");
                    return ReturnStatus::FAILURE;
                }
                addNewConnection(ePollFDs, newSocket);
            } else {
                // Ready to read data
                if (ePollEvents[i].events & EPOLLIN) {
                    char buffer[SocketUtility::bufferSize] = {0};
                    long readValue = read(ePollEvents[i].data.fd, buffer, sizeof(buffer));
                    if (readValue < 0) {
                        if (errno == EPIPE) {
                            std::cout << "SIGPIPE on socket " << ePollEvents[i].data.fd << std::endl;
                            closeConnection(ePollFDs, ePollEvents[i].data.fd);
                        }
                    } else {
                        readyForWriteConnection(ePollFDs, ePollEvents[i].data.fd);
                    }
                } else {
                    // Data is ready to be sent
                    if (ePollEvents[i].events & EPOLLOUT) {
                        auto signal = write(ePollEvents[i].data.fd, hello, strlen(hello));
                        if (signal < 0) {
                            if (errno == EPIPE) {
                                std::cout << "SIGPIPE on socket " << ePollEvents[i].data.fd << std::endl;
                                closeConnection(ePollFDs, ePollEvents[i].data.fd);
                            }
                        } else {
                            readyForReadConnection(ePollFDs, ePollEvents[i].data.fd);
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
