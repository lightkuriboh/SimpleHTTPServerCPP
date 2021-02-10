
#ifndef SIMPLECPPSERVER_UNIXSTANDARDUTILITY_H
#define SIMPLECPPSERVER_UNIXSTANDARDUTILITY_H

#include <string>

namespace LibraryWrapper {
    class UnixStandard {
    public:
        static void closeFileDescriptor(const int &fileDescriptor);

        static void writeToSockFd(const int &socketFileDescriptor, const std::string &resp);
    };
};

#endif //SIMPLECPPSERVER_UNIXSTANDARDUTILITY_H
