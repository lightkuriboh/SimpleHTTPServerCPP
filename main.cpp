#include <iostream>
#include "Server/MyServer.h"
#include "SignalHandler/SignalHandler.h"
#include "MockClients/MockClients.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

//    Client::MockClients::spawningClient(5);
    Signals::SignalHandler::setSignalHanders();

//    Server::MyServer myServer = Server::MyServer(true, false);
    Server::MyServer myServer = Server::MyServer(true, true);
//    Server::MyServer myServer = Server::MyServer(false, false);
//    Server::MyServer myServer = Server::MyServer();
    myServer.start();

    return 0;
}
