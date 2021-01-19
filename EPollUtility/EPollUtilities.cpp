//
// Created by kuribohkute on 15/01/2020.
//

#include "EPollUtilities.h"

#include <sys/epoll.h>

void EPollUtility::EPollUtilities::registerToEPoll(const int &context, const int &socketfd, unsigned int ePollEvent, int actionType) {
    epoll_event event = epoll_event();
    event.data.fd = socketfd;
    event.events = ePollEvent;
    epoll_ctl(context, actionType, event.data.fd, &event);
}

