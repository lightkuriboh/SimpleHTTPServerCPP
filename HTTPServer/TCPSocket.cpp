
#include "HTTPServer/TCPSocket.h"

#include <iostream>

#include "libs/SocketUtility.h"
#include "libs/UnixStandardUtility.h"

SimpleHTTPServer::TCPSocket::TCPSocket(const Utils::Config &config) {
    this->initConfig(config);

    if (this->createSocket() == ReturnStatus::SUCCESS) {
        if (this->socketOptions() == ReturnStatus::SUCCESS) {
            if (this->identifySocket() == ReturnStatus::SUCCESS) {
                if (this->makeSocketListening() == ReturnStatus::SUCCESS) {
                    std::cout << "Started socket successfully on port " << activePORT << std::endl;
                    return;
                }
            }
        }
        LibraryWrapper::UnixStandard::closeFileDescriptor(this->socketMaster);
    }
    exit(1);
}

ReturnStatus SimpleHTTPServer::TCPSocket::createSocket() {
    this->socketMaster = LibraryWrapper::Socket::createTCPSocket();
    if (LibraryWrapper::Socket::createSocketSuccessfully(this->socketMaster)) {
        return ReturnStatus::SUCCESS;
    }

    perror("Error creating socket");
    return ReturnStatus::FAILURE;
}

ReturnStatus SimpleHTTPServer::TCPSocket::socketOptions() const {
    if (LibraryWrapper::Socket::setSocketOptionsSuccessfully(this->socketMaster, this->socketOption)) {
        return ReturnStatus::SUCCESS;
    }

    perror("Error setting up socket options");
    return ReturnStatus::FAILURE;
}

ReturnStatus SimpleHTTPServer::TCPSocket::identifySocket() {
    this->address = LibraryWrapper::Socket::setUpSocketAddress(this->activePORT);
    if (LibraryWrapper::Socket::bindSocketSuccessfully(this->socketMaster, this->address)) {
        return ReturnStatus::SUCCESS;
    }

    perror("Error binding socket");
    return ReturnStatus::FAILURE;
}

ReturnStatus SimpleHTTPServer::TCPSocket::makeSocketListening() const {
    if (LibraryWrapper::Socket::listenOnSocketSuccessfully(this->socketMaster,
                                                           this->maximumPendingConnection)) {
        return ReturnStatus::SUCCESS;
    }

    perror("Error listening socket");
    return ReturnStatus::FAILURE;
}

void SimpleHTTPServer::TCPSocket::initConfig(const Utils::Config &config) {
    this->activePORT = config.getPort();
    this->maximumPendingConnection = config.getMaximumPendingConnections();
}
