#include <iostream>
#include "SocketUtility/TCPSocket.h"
#include "SignalHandler/SignalHandler.h"
#include "MockClients/MockClients.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    Client::MockClients::spawningClient(5);

    Signals::SignalHandler::setSignalHanders();
    SocketUtility::TCPSocket tcpSocket = SocketUtility::TCPSocket();
    tcpSocket.start();
    return 0;
}
