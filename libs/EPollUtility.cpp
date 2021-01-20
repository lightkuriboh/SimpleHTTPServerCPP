
#include "EPollUtility.h"

#include <unistd.h>

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

int LibraryWrapper::EPoll::getChangedEPollEvents(const int &ePollContext, std::vector<epoll_event> &epollEvents) {
    return epoll_wait(ePollContext, &*epollEvents.begin(), epollEvents.size(), 0);
}

bool LibraryWrapper::EPoll::errorOccurredWithEPollEvent(const epoll_event &ePollEvent) {
    return ePollEvent.events & EPOLLERR;
}

bool LibraryWrapper::EPoll::clientClosedTheConnection(const epoll_event &ePollEvent) {
    return ePollEvent.events & EPOLLHUP;
}

int LibraryWrapper::EPoll::creatEPollContext(const int &ePollSize) {
    return epoll_create(ePollSize);
}

