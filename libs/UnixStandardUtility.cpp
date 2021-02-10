
#include "libs/UnixStandardUtility.h"

#include <unistd.h>

#include <cstring>

void LibraryWrapper::UnixStandard::closeFileDescriptor(const int &fileDescriptor) {
    close(fileDescriptor);
}

void LibraryWrapper::UnixStandard::writeToSockFd(const int &socketFileDescriptor, const std::string &resp) {
    auto signal = write(socketFileDescriptor, &*resp.begin(), strlen(&*resp.begin()));
}

int LibraryWrapper::UnixStandard::writeToSockFd(const int &socketFileDescriptor, const char *bufferPtr,
                                                 const int &bufferSize) {
    return write(socketFileDescriptor, bufferPtr, bufferSize);
}
