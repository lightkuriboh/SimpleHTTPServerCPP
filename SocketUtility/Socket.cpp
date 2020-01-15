//
// Created by kuribohkute on 14/01/2020.
//
#include "Socket.h"

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
    if (setsockopt(this->socketMaster, SOL_SOCKET, SO_REUSEPORT, &this->socketOption, sizeof(this->socketOption))) {
        perror("setsockopt");
        return ReturnStatus::FAILURE;
    }
    return ReturnStatus::SUCCESS;
}

void SocketUtility::Socket::setUpAddress(int port) {
    delete this->address;
    this->address = new sockaddr_in();
    this->addressLength = sizeof(&address);

    this->address->sin_family = communicationDomain;
    this->address->sin_addr.s_addr = INADDR_ANY;
    this->address->sin_port = htons(port);
}

ReturnStatus SocketUtility::Socket::identifySocket() {
    bool boundSuccess = false;
    for (int counter = 0; counter < 1000; ++counter) {
        this->setUpAddress(SocketUtility::PORT + counter);
        if (bind(this->socketMaster, (sockaddr*) this->address, sizeof(*this->address)) < 0) {
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

