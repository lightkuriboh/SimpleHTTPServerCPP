#include <iostream>

#include "Server/MyServer.h"
#include "SignalHandler/SignalHandler.h"

int main() {
    Signals::SignalHandler::setSignalHanders();

//    ServerNS::MyServer myServer =  ServerNS::MyServer(true);
    ServerNS::MyServer myServer = ServerNS::MyServer();
    myServer.start();

    return 0;
}
