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
    private:
        bool onlyPureRequest = false;
    public:
        virtual ~Server() = default;
        virtual ReturnStatus handleRequest(const int &sockfd) = 0;
        virtual ReturnStatus writingResponse(const int &sockfd, const int &context, void (*callback)(const int&, const int&)) = 0;
        bool getOnlyPureRequest();
        void setOnlyPureRequest(bool _onlyPureRequest);
    };
};

#endif //DTLMINIPROJECT_SERVER_H
