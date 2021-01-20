
#include "libs/SocketUtility.h"

int LibraryWrapper::Socket::createTCPSocket() {
    return socket(IP_V4_ADDRESS, TCP_COMMUNICATION_TYPE, DEFAULT_SOCKET_PROTOCOL);
}

bool LibraryWrapper::Socket::createSocketSuccessfully(const int &socketFileDescriptor) {
    return socketFileDescriptor >= 0;
}

bool LibraryWrapper::Socket::setSocketOptionsSuccessfully(const int &socketFileDescriptor, const int &socketOption) {
    return setsockopt(socketFileDescriptor, SOCKET_LAYER_LEVEL, REUSE_SOCKET_ADDRESS, &socketOption, sizeof(int)) >= 0;
}

bool LibraryWrapper::Socket::bindSocketSuccessfully(const int &socketFileDescriptor, const sockaddr_in &address) {
    return bind(socketFileDescriptor, (struct sockaddr*) &address, sizeof(struct sockaddr)) >= 0;
}

sockaddr_in LibraryWrapper::Socket::setUpSocketAddress(const int &port) {
    sockaddr_in address{};
    address.sin_family = IP_V4_ADDRESS;
    address.sin_addr.s_addr = ACCEPT_ANY_ADDRESS;
    address.sin_port = htons(port);
    return address;
}

bool LibraryWrapper::Socket::listenOnSocketSuccessfully(const int &socketFileDescriptor,
                                                        const int &maximalPendingConnection) {
    return listen(socketFileDescriptor, maximalPendingConnection) >= 0;
}

int LibraryWrapper::Socket::acceptNewConnection(const int &socketHost) {
    sockaddr clientAddress{};
    socklen_t clientAddressLength = sizeof(clientAddress);

    return accept(socketHost, &clientAddress, &clientAddressLength);
}
