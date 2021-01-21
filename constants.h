//
// Created by kuribohkute on 14/01/2020.
//

#ifndef SIMPLECPPSERVER_CONSTANTS_H
#define SIMPLECPPSERVER_CONSTANTS_H

enum class ReturnStatus {
    SUCCESS,
    FAILURE
};

namespace SimpleHTTPServer {
    constexpr int bufferSize = 2048;
}

#endif //SIMPLECPPSERVER_CONSTANTS_H
