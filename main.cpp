
#include "Server/MyServer.h"
#include "SignalHandler/SignalHandler.h"

int main() {
    Signals::setSignalHandlers();

    ServerNS::MyServer myServer = ServerNS::MyServer();
    myServer.start();

    return 0;
}
