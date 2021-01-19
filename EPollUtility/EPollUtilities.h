//
// Created by kuribohkute on 15/01/2020.
//

#ifndef SIMPLECPPSERVER_EPOLLUTILITY_H
#define SIMPLECPPSERVER_EPOLLUTILITY_H

namespace EPollUtility {
    class EPollUtilities {
    public:
        static void registerToEPoll(const int &context, const int &socketfd, unsigned int ePollEvent, int actionType);
    };
}

#endif //SIMPLECPPSERVER_EPOLLUTILITY_H
