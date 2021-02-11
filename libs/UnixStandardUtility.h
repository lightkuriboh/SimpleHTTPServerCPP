
#ifndef SIMPLECPPSERVER_UNIXSTANDARDUTILITY_H
#define SIMPLECPPSERVER_UNIXSTANDARDUTILITY_H

#include <string>

namespace LibraryWrapper {
    class UnixStandard {
    public:
        static void closeFileDescriptor(const int &fileDescriptor);

        static int writeToSockFd(const int &socketFileDescriptor, char const *bufferPtr, const int &bufferSize);
        static void writeToSockFd(const int &socketFileDescriptor, const std::string &resp);

        static std::string readFromSocketFileDescriptor(const int &socketFileDescriptor, const int &bufferSize);
    };
};

#endif //SIMPLECPPSERVER_UNIXSTANDARDUTILITY_H
