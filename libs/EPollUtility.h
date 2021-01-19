
#ifndef SIMPLECPPSERVER_EPOLLUTILITY_H
#define SIMPLECPPSERVER_EPOLLUTILITY_H

namespace LibraryWrapper {
    class EPoll {
    private:
        static void updateToEPoll(const int &context, const int &socketFileDescriptor,
                                  unsigned int ePollEvent, int actionType);
    public:
        static void removeFromEpoll(const int &context, const int &socketFileDescriptor);
        static void addToEpoll(const int &context, const int &socketFileDescriptor);
    };
}

#endif //SIMPLECPPSERVER_EPOLLUTILITY_H
