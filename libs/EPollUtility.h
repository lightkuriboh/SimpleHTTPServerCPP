
#ifndef SIMPLECPPSERVER_EPOLLUTILITY_H
#define SIMPLECPPSERVER_EPOLLUTILITY_H

#include "sys/epoll.h"

#include <vector>

namespace LibraryWrapper {
    class EPoll {
    private:
        static void updateToEPoll(const int &context, const int &socketFileDescriptor,
                                  unsigned int ePollEvent, int actionType);
    public:
        static void removeFromEpoll(const int &context, const int &socketFileDescriptor);
        static void addToEpoll(const int &context, const int &socketFileDescriptor);

        static int getChangedEPollEvents(const int &ePollContext, std::vector<epoll_event>& epollEvents);
        static bool errorOccurredWithEPollEvent(const epoll_event &ePollEvent);
        static bool clientClosedTheConnection(const epoll_event &ePollEvent);
    };
}

#endif //SIMPLECPPSERVER_EPOLLUTILITY_H
