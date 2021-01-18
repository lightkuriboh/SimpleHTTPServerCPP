//
// Created by kuribohkute on 15/01/2020.
//

#ifndef SIMPLECPPSERVER_SERVER_H
#define SIMPLECPPSERVER_SERVER_H

#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "../constants.h"

namespace ServerNS {
    class Server {
    public:
        virtual ~Server() = default;
        virtual void handleRequest(const int &sockfd) = 0;
    };
};

#endif //SIMPLECPPSERVER_SERVER_H
