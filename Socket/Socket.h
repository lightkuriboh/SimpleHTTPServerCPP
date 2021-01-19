
#ifndef SIMPLECPPSERVER_SOCKET_H
#define SIMPLECPPSERVER_SOCKET_H

#include <netinet/in.h>

#include "constants.h"

namespace SimpleHTTPServer {
    class Socket {
    private:
        int communicationDomain = AF_INET;
        int communicationType = SOCK_STREAM;
        int socketProtocol = 0;
        int socketOption = 0;
        int activePORT = SimpleHTTPServer::PORT;

        ReturnStatus createSocket();
        ReturnStatus socketOptions();
        void setUpAddress(int port);
        ReturnStatus identifySocket();

    protected:
        sockaddr_in address{};
        sockaddr clientAddress{};
        socklen_t clientAddressLength = 0;

        int socketMaster = 0;

        virtual ReturnStatus makeSocketListening() = 0;
        virtual ReturnStatus listeningConnections() = 0;
        virtual void startingSocket() = 0;
        void initSocket(int _communicationDomain, int _communicationType);
    public:
        void start();
        Socket();
    };
}

#endif //SIMPLECPPSERVER_SOCKET_H
