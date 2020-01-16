//
// Created by kuribohkute on 15/01/2020.
//

#include "MyServer.h"

ReturnStatus Server::MyServer::handleRequest(const int &sockfd) {
    char buffer[SocketUtility::bufferSize] = {0};
    auto readValue = read(sockfd, buffer, sizeof(buffer));
//    printf("%s", buffer);
    if (readValue <= 0) {
        return ReturnStatus::FAILURE;
    }
    this->responses[sockfd] = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
    return ReturnStatus::SUCCESS;
}

ReturnStatus Server::MyServer::writingResponse(const int &sockfd, const int &context, void (*callback)(const int&, const int&)) {
    std::string hello = this->responses[sockfd];
//    std::string hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
    auto signal = write(sockfd, &*hello.begin(), strlen(&*hello.begin()));
    if (signal <= 0) {
        return ReturnStatus::FAILURE;
    }
    (*callback)(context, sockfd);
    return ReturnStatus::SUCCESS;
}

Server::MyServer::MyServer(bool _onlyPureRequest, bool _cleanTerminatedConnections) {
    this->tcpSocket = new SocketUtility::TCPSocket(_cleanTerminatedConnections);
    this->tcpSocket->initServer(this);
    this->setOnlyPureRequest(_onlyPureRequest);
}

Server::MyServer::~MyServer() {
    delete this->tcpSocket;
}

void Server::MyServer::start() {
    tcpSocket->start();
}

