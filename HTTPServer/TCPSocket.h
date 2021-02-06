
#ifndef SIMPLECPPSERVER_TCPSOCKET_H
#define SIMPLECPPSERVER_TCPSOCKET_H

#include <netinet/in.h>

#include "constants.h"
#include "utils/ConfigParser.h"

namespace SimpleHTTPServer {
    class TCPSocket {
    private:
        int activePORT = 3000;
        int maximumPendingConnection = 1000;

        sockaddr_in address{};
        int socketOption = 0;
        int socketMaster = 0;

        void initConfig(const Utils::Config &config);
        ReturnStatus createSocket();
        ReturnStatus identifySocket();
        [[nodiscard]] ReturnStatus socketOptions() const;
        [[nodiscard]] ReturnStatus makeSocketListening() const;
    public:
        explicit TCPSocket(const Utils::Config &config);

        [[nodiscard]] int getSocketMaster() const { return this->socketMaster; }
    };
}

#endif //SIMPLECPPSERVER_TCPSOCKET_H
