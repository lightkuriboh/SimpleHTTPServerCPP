
#ifndef SIMPLECPPSERVER_UNIXSTANDARDUTILITY_H
#define SIMPLECPPSERVER_UNIXSTANDARDUTILITY_H

namespace LibraryWrapper {
    class UnixStandard {
    public:
        static void closeFileDescriptor(const int &fileDescriptor);
    };
};

#endif //SIMPLECPPSERVER_UNIXSTANDARDUTILITY_H
