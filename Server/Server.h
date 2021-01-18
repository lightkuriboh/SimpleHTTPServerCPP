//
// Created by kuribohkute on 15/01/2020.
//

#ifndef DTLMINIPROJECT_SERVER_H
#define DTLMINIPROJECT_SERVER_H

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

#endif //DTLMINIPROJECT_SERVER_H
