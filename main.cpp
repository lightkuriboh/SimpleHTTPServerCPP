
#include "HTTPServer/HTTPServer.h"
#include "utils/ConfigParser.h"

int main() {

    SimpleHTTPServer::HTTPServer myServer = SimpleHTTPServer::HTTPServer();
    myServer.start();

    return 0;
}
