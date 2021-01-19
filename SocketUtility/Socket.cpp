
#include "Socket.h"

#include <sys/socket.h>
#include <unistd.h>

#include <cstdio>
#include <iostream>

ReturnStatus SocketUtility::Socket::createSocket() {
    this->socketMaster = socket(this->communicationDomain, this->communicationType, this->socketProtocol);

    // socket(...) return -1 if it failed on creating socket
    if (this->socketMaster < 0) {
        perror("Error creating socket");

        return ReturnStatus::FAILURE;
    }
    return ReturnStatus::SUCCESS;
}

ReturnStatus SocketUtility::Socket::socketOptions() {
    if (setsockopt(this->socketMaster, SOL_SOCKET, SO_REUSEPORT, &this->socketOption, sizeof(int))) {
        perror("setsockopt");
        return ReturnStatus::FAILURE;
    }
    return ReturnStatus::SUCCESS;
}

void SocketUtility::Socket::setUpAddress(int port) {
    this->address.sin_family = communicationDomain;
    this->address.sin_addr.s_addr = INADDR_ANY;
    this->address.sin_port = htons(port);
}

ReturnStatus SocketUtility::Socket::identifySocket() {
    bool boundSuccess = false;
    for (int counter = 0; counter < 1000; ++counter) {
        this->setUpAddress(SocketUtility::PORT + counter);
        if (bind(this->socketMaster, (struct sockaddr*) &this->address, sizeof(struct sockaddr)) < 0) {
            continue;
        }
        boundSuccess = true;
        this->activePORT = PORT + counter;
        break;
    }
    if (!boundSuccess) {
        return ReturnStatus::FAILURE;
    }
    return ReturnStatus::SUCCESS;
}

void SocketUtility::Socket::start() {
    if (this->createSocket() == ReturnStatus::SUCCESS && this->socketOptions() == ReturnStatus::SUCCESS) {

        if (this->identifySocket() == ReturnStatus::SUCCESS) {
            std::cout << "Started socket successfully on port " << activePORT << std::endl;
            this->startingSocket();
        }
        close(this->socketMaster);
    }
}

void SocketUtility::Socket::initSocket(int _communicationDomain, int _communicationType) {
    this->communicationDomain = _communicationDomain;
    this->communicationType = _communicationType;
}

SocketUtility::Socket::Socket() {
    this->clientAddress = sockaddr{};
    this->clientAddressLength = sizeof(this->clientAddress);
    this->address = sockaddr_in{};

}

