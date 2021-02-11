
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

std::string LibraryWrapper::UnixStandard::readFromSocketFileDescriptor(
        const int &socketFileDescriptor, const int &bufferSize) {
    std::string buffer(bufferSize, 0);
    auto readValue = read(socketFileDescriptor, &buffer[0], buffer.size());
    if (readValue < 0) {
        return "";
    }
    return buffer.substr(0, readValue);
}
