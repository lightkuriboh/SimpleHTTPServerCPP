//
// Created by kuribohkute on 14/01/2020.
//

#ifndef DTLMINIPROJECT_CONSTANTS_H
#define DTLMINIPROJECT_CONSTANTS_H

enum class ReturnStatus {
    SUCCESS,
    FAILURE
};

namespace SocketUtility {
    constexpr int maximumPendingConnections = 10000;
    constexpr int maximumConnections = 10000;
    constexpr int bufferSize = 4096;
    constexpr int PORT = 8080;
}

#endif //DTLMINIPROJECT_CONSTANTS_H
