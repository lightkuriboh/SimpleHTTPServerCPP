
#include "HTTPServer/HTTPServer.h"
#include "utils/SignalHandlers.h"

int main() {
    SignalHandlers::setSignalHandlers();

    SimpleHTTPServer::HTTPServer myServer = SimpleHTTPServer::HTTPServer();
    myServer.start();

    return 0;
}
