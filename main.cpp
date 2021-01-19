
#include "Server/MyServer.h"
#include "SignalHandler/SignalHandler.h"

int main() {
    Signals::setSignalHandlers();

    SimpleCPPServer::MyServer myServer = SimpleCPPServer::MyServer();
    myServer.start();

    return 0;
}
