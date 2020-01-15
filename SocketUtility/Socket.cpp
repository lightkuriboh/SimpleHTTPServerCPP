//
// Created by kuribohkute on 14/01/2020.
//
#include "Socket.h"

ReturnStatus SocketUtility::Socket::createSocket() {
    socketMaster = socket(communicationDomain, communicationType, socketProtocol);

    // socket(...) return -1 if it failed on creating socket
    if (socketMaster < 0) {
        perror("Error creating socket");

        return ReturnStatus::FAILURE;
    }
    return ReturnStatus::SUCCESS;
}

ReturnStatus SocketUtility::Socket::socketOptions() {
    if (setsockopt(socketMaster, SOL_SOCKET, SO_REUSEPORT, &socketOption, sizeof(socketOption))) {
        perror("setsockopt");
        return ReturnStatus::FAILURE;
    }
    return ReturnStatus::SUCCESS;
}

void SocketUtility::Socket::setUpAddress(int port) {
    delete address;
    address = new sockaddr_in();
    addressLength = sizeof(&address);

    address->sin_family = communicationDomain;
    address->sin_addr.s_addr = INADDR_ANY;
    address->sin_port = htons(port);
}

ReturnStatus SocketUtility::Socket::identifySocket() {
    bool boundSuccess = false;
    for (int counter = 0; counter < 1000; ++counter) {
        setUpAddress(SocketUtility::PORT + counter);
        if (bind(socketMaster, (sockaddr*) address, sizeof(*address)) < 0) {
            continue;
        }
        boundSuccess = true;
        activePORT = PORT + counter;
        break;
    }
    if (!boundSuccess) {
        return ReturnStatus::FAILURE;
    }
    return ReturnStatus::SUCCESS;
}

void SocketUtility::Socket::start() {

    if (createSocket() == ReturnStatus::SUCCESS && socketOptions() == ReturnStatus::SUCCESS) {

        if (identifySocket() == ReturnStatus::SUCCESS) {
            std::cout << "Started socket successfully on port " << activePORT << std::endl;
            startingSocket();
        }
        close(socketMaster);
    }
}

void SocketUtility::Socket::initSocket(int _communicationDomain, int _communicationType) {
    communicationDomain = _communicationDomain;
    communicationType = _communicationType;
}

