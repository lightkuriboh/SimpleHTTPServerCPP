//
// Created by kuribohkute on 14/01/2020.
//

#ifndef DTLMINIPROJECT_TCPSOCKET_H
#define DTLMINIPROJECT_TCPSOCKET_H

#include "Socket.h"
namespace SocketUtility {
    class TCPSocket : public Socket {
    private:
        ReturnStatus makeSocketListening() override;
        ReturnStatus listeningConnections() override;
        void startingSocket() override;
    public:
        TCPSocket();
    };
}

#endif //DTLMINIPROJECT_TCPSOCKET_H
