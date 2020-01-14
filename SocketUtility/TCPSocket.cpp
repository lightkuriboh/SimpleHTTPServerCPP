//
// Created by kuribohkute on 14/01/2020.
//
#include "TCPSocket.h"

SocketUtility::TCPSocket::TCPSocket() {
    initSocket(AF_INET, SOCK_STREAM);
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
    char *hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";

    while (true) {
        printf("\n+++++++ Waiting for new connection ++++++++\n\n");
        int newSocket = accept(socketMaster, (sockaddr *) address, (socklen_t *) &addressLength);
        if (newSocket < 0) {
            perror("Accepting already");
            return ReturnStatus::FAILURE;
        }

        char buffer[SocketUtility::bufferSize] = {0};
        long readValue = read(newSocket, buffer, sizeof(buffer));
        if (readValue < 0) {
            return ReturnStatus::FAILURE;
        }
        printf("%s\n", buffer);
        write(newSocket , hello , strlen(hello));
        printf("------------------Hello message sent-------------------\n");
        close(newSocket);

    }
}

void SocketUtility::TCPSocket::startingSocket() {
    if (makeSocketListening() == ReturnStatus::SUCCESS) {
        listeningConnections();
    }
}
