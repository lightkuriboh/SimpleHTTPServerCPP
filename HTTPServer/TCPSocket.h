
#ifndef SIMPLECPPSERVER_TCPSOCKET_H
#define SIMPLECPPSERVER_TCPSOCKET_H

#include <netinet/in.h>

#include "constants.h"

namespace SimpleHTTPServer {
    class TCPSocket {
    private:
        sockaddr_in address{};
        int socketOption = 0;
        int activePORT = SimpleHTTPServer::PORT;
        int socketMaster = 0;

        ReturnStatus createSocket();
        ReturnStatus identifySocket();
        [[nodiscard]] ReturnStatus socketOptions() const;
        [[nodiscard]] ReturnStatus makeSocketListening() const;
    public:
        TCPSocket();

        [[nodiscard]] int getSocketMaster() const { return this->socketMaster; }
    };
}

#endif //SIMPLECPPSERVER_TCPSOCKET_H
