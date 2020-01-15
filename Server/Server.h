//
// Created by kuribohkute on 15/01/2020.
//

#ifndef DTLMINIPROJECT_SERVER_H
#define DTLMINIPROJECT_SERVER_H

#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/socket.h>
#include "../constants.h"

namespace Server {
    class Server {
    public:
        virtual ~Server() = default;
        virtual ReturnStatus handleRequest(int sockfd) = 0;
        virtual ReturnStatus writingResponse(int sockfd, int context, void (*callback)(int, int)) = 0;
    };
};

#endif //DTLMINIPROJECT_SERVER_H
