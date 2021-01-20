
#ifndef SIMPLECPPSERVER_TCPSOCKET_H
#define SIMPLECPPSERVER_TCPSOCKET_H

#include <netinet/in.h>

#include "constants.h"

namespace SimpleHTTPServer {
    class TCPSocket {
    private:
        int socketOption = 0;
        int activePORT = SimpleHTTPServer::PORT;
        sockaddr_in address{};

        ReturnStatus createSocket();
        ReturnStatus identifySocket();
        [[nodiscard]] ReturnStatus socketOptions() const;
        [[nodiscard]] ReturnStatus makeSocketListening() const;

        int socketMaster = 0;
    public:
        TCPSocket();

        [[nodiscard]] int getSocketMaster() const { return this->socketMaster; }
    };
}

#endif //SIMPLECPPSERVER_TCPSOCKET_H
