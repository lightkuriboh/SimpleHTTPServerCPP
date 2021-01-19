//
// Created by kuribohkute on 14/01/2020.
//

#ifndef SIMPLECPPSERVER_CONSTANTS_H
#define SIMPLECPPSERVER_CONSTANTS_H

enum class ReturnStatus {
    SUCCESS,
    FAILURE
};

namespace SimpleCPPServer {
    constexpr int maximumPendingConnections = 1000;
    constexpr int maximumConnections = 20000;
    constexpr int bufferSize = 2048;
    constexpr int PORT = 2101;
}

#endif //SIMPLECPPSERVER_CONSTANTS_H
