
#include "HTTPServer/TCPSocket.h"

#include <sys/socket.h>
#include <unistd.h>

#include <iostream>

SimpleHTTPServer::TCPSocket::TCPSocket() {
    if (this->createSocket() == ReturnStatus::SUCCESS) {
        if (this->socketOptions() == ReturnStatus::SUCCESS) {
            if (this->identifySocket() == ReturnStatus::SUCCESS) {
                if (this->makeSocketListening() == ReturnStatus::SUCCESS) {
                    std::cout << "Started socket successfully on port " << activePORT << std::endl;
                    return;
                }
            }
        }
        close(this->socketMaster);
    }
    exit(1);
}

ReturnStatus SimpleHTTPServer::TCPSocket::createSocket() {
    this->socketMaster = socket(this->communicationDomain, this->communicationType, this->socketProtocol);
    if (this->socketMaster < 0) {
        perror("Error creating socket");
        return ReturnStatus::FAILURE;
    }
    return ReturnStatus::SUCCESS;
}

ReturnStatus SimpleHTTPServer::TCPSocket::socketOptions() {
    if (setsockopt(this->socketMaster, SOL_SOCKET, SO_REUSEADDR, &this->socketOption, sizeof(int))) {
        perror("setsockopt");
        return ReturnStatus::FAILURE;
    }
    return ReturnStatus::SUCCESS;
}

void SimpleHTTPServer::TCPSocket::setUpAddress(int port) {
    this->address.sin_family = communicationDomain;
    this->address.sin_addr.s_addr = INADDR_ANY;
    this->address.sin_port = htons(port);
}

ReturnStatus SimpleHTTPServer::TCPSocket::identifySocket() {
    this->setUpAddress(this->activePORT);
    if (bind(this->socketMaster, (struct sockaddr*) &this->address, sizeof(struct sockaddr)) < 0) {
        perror("error binding socket");
        return ReturnStatus::FAILURE;
    }
    return ReturnStatus::SUCCESS;
}

ReturnStatus SimpleHTTPServer::TCPSocket::makeSocketListening() const {
    if (listen(this->socketMaster, SimpleHTTPServer::maximumPendingConnections) < 0) {
        perror("Listening already");
        return ReturnStatus::FAILURE;
    }
    return ReturnStatus::SUCCESS;
}
