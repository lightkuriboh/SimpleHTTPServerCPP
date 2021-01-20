
#include "HTTPServer/HTTPServer.h"

int main() {

    SimpleHTTPServer::HTTPServer myServer = SimpleHTTPServer::HTTPServer();
    myServer.start();

    return 0;
}
