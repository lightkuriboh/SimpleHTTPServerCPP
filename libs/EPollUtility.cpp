
#include "EPollUtility.h"

#include <sys/epoll.h>

void LibraryWrapper::EPoll::updateToEPoll(const int &context, const int &socketFileDescriptor,
                                          unsigned int ePollEvent, int actionType) {
    epoll_event event = epoll_event();
    event.data.fd = socketFileDescriptor;
    event.events = ePollEvent;
    epoll_ctl(context, actionType, event.data.fd, &event);
}

void LibraryWrapper::EPoll::removeFromEpoll(const int &context, const int &socketFileDescriptor) {
    LibraryWrapper::EPoll::updateToEPoll(context, socketFileDescriptor, EPOLLERR, EPOLL_CTL_DEL);
}

void LibraryWrapper::EPoll::addToEpoll(const int &context, const int &socketFileDescriptor) {
    LibraryWrapper::EPoll::updateToEPoll(context, socketFileDescriptor, EPOLLIN, EPOLL_CTL_ADD);
}

