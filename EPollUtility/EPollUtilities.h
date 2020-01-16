//
// Created by kuribohkute on 15/01/2020.
//

#ifndef DTLMINIPROJECT_EPOLLUTILITY_H
#define DTLMINIPROJECT_EPOLLUTILITY_H

#include <sys/epoll.h>

namespace EPollUtility {
    class EPollUtilities {
    public:
        static void registerToEPoll(const int &context, const int &socketfd, unsigned int ePollEvent, int actionType);
    };
}

#endif //DTLMINIPROJECT_EPOLLUTILITY_H
