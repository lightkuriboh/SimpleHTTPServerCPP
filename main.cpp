#include <iostream>
#include "Server/MyServer.h"
#include "SignalHandler/SignalHandler.h"
#include "MockClients/MockClients.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

//    Client::MockClients::spawningClient(5);
    Signals::SignalHandler::setSignalHanders();

    ServerNS::MyServer myServer = ServerNS::MyServer();
    myServer.start();

    return 0;
}
