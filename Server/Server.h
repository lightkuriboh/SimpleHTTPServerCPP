//
// Created by kuribohkute on 15/01/2020.
//

#ifndef SIMPLECPPSERVER_SERVER_H
#define SIMPLECPPSERVER_SERVER_H

#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <iostream>

#include "constants.h"

namespace ServerNS {
    class Server {
    public:
        virtual ~Server() = default;
        virtual void handleRequest(const int &sockfd) = 0;
    };
};

#endif //SIMPLECPPSERVER_SERVER_H
