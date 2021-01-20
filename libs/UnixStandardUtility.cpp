
#include "libs/UnixStandardUtility.h"

#include <unistd.h>

void LibraryWrapper::UnixStandard::closeFileDescriptor(const int &fileDescriptor) {
    close(fileDescriptor);
}
