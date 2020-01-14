#include <iostream>
#include "SocketUtility/TCPSocket.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    SocketUtility::TCPSocket tcpSocket = SocketUtility::TCPSocket();
    tcpSocket.start();
    return 0;
}
