//
// Created by kuribohkute on 15/01/2020.
//

#ifndef DTLMINIPROJECT_MOCKCLIENTS_H
#define DTLMINIPROJECT_MOCKCLIENTS_H

#include <chrono>
#include <cstring>
#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include "../constants.h"

namespace Client {
    class MockClients {
    public:
        static void spawningClient(int numberClients);
    };
}

#endif //DTLMINIPROJECT_MOCKCLIENTS_H
