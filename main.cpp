
#include "HTTPServer/HTTPServer.h"
#include "SignalHandler/SignalHandler.h"

int main() {
    Signals::setSignalHandlers();

    SimpleHTTPServer::HTTPServer myServer = SimpleHTTPServer::HTTPServer();
    myServer.start();

    return 0;
}
