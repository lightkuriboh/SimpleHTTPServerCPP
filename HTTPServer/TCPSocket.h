
#ifndef SIMPLECPPSERVER_TCPSOCKET_H
#define SIMPLECPPSERVER_TCPSOCKET_H

#include <netinet/in.h>

#include "constants.h"

namespace SimpleHTTPServer {
    class TCPSocket {
    private:
        int communicationDomain = AF_INET;
        int communicationType = SOCK_STREAM;
        int socketProtocol = 0;
        int socketOption = 0;
        int activePORT = SimpleHTTPServer::PORT;
        sockaddr_in address{};

        ReturnStatus createSocket();
        ReturnStatus socketOptions();
        ReturnStatus identifySocket();
        [[nodiscard]] ReturnStatus makeSocketListening() const;
        void setUpAddress(int port);

        int socketMaster = 0;
    public:
        TCPSocket();

        [[nodiscard]] int getSocketMaster() const { return this->socketMaster; }
    };
}

#endif //SIMPLECPPSERVER_TCPSOCKET_H
