
#ifndef SIMPLECPPSERVER_SOCKETUTILITY_H
#define SIMPLECPPSERVER_SOCKETUTILITY_H

#include <netinet/in.h>

namespace LibraryWrapper {
    class Socket {
    private:
        static const int ACCEPT_ANY_ADDRESS = INADDR_ANY;
        static const int DEFAULT_SOCKET_PROTOCOL = 0;
        static const int IP_V4_ADDRESS = AF_INET;
        static const int REUSE_SOCKET_ADDRESS = SO_REUSEPORT;
        static const int SOCKET_LAYER_LEVEL = SOL_SOCKET;
        static const int TCP_COMMUNICATION_TYPE = SOCK_STREAM;

    public:
        static sockaddr_in setUpSocketAddress(const int &port);

        static int createTCPSocket();
        static int acceptNewConnection(const int &socketHost);

        static bool bindSocketSuccessfully(const int &socketFileDescriptor, const sockaddr_in &address);
        static bool createSocketSuccessfully(const int &socketFileDescriptor);
        static bool listenOnSocketSuccessfully(const int &socketFileDescriptor, const int &maximalPendingConnection);
        static bool setSocketOptionsSuccessfully(const int &socketFileDescriptor, const int &socketOption);
    };
}

#endif //SIMPLECPPSERVER_SOCKETUTILITY_H
