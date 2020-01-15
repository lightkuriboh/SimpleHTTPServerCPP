//
// Created by kuribohkute on 15/01/2020.
//

#include "MyServer.h"

ReturnStatus Server::MyServer::handleRequest(int sockfd) {
    char buffer[SocketUtility::bufferSize] = {0};
    auto readValue = read(sockfd, buffer, sizeof(buffer));
//    printf("%s", buffer);
    if (readValue < 0) {
        if (errno == EPIPE) {
            return ReturnStatus::FAILURE;
        }
    }
    return ReturnStatus::SUCCESS;
}

ReturnStatus Server::MyServer::writingResponse(int sockfd, int context, void (*callback)(int, int)) {
    std::string hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
    auto signal = write(sockfd, &*hello.begin(), strlen(&*hello.begin()));
    if (signal <= 0) {
        return ReturnStatus::FAILURE;
    }
    (*callback)(context, sockfd);
    return ReturnStatus::SUCCESS;
}

Server::MyServer::MyServer() {
    this->tcpSocket = new SocketUtility::TCPSocket();
    this->tcpSocket->initServer(this);
}

Server::MyServer::~MyServer() {
    delete this->tcpSocket;
}

void Server::MyServer::start() {
    tcpSocket->start();
}

