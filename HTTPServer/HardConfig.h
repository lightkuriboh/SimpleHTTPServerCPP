//
// Created by kuribohkute on 14/01/2020.
//

#ifndef SIMPLECPPSERVER_HARDCONFIG_H
#define SIMPLECPPSERVER_HARDCONFIG_H

enum class ReturnStatus {
    SUCCESS,
    FAILURE
};

namespace SimpleHTTPServer {
    class HardConfig {
    public:
        static constexpr int ioBufferSize = 2048;
    };
}

#endif //SIMPLECPPSERVER_HARDCONFIG_H
