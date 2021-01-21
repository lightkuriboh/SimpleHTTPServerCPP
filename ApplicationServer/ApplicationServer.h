
#ifndef SIMPLECPPSERVER_APPLICATIONSERVER_H
#define SIMPLECPPSERVER_APPLICATIONSERVER_H

#include <map>

#include "HTTPServer/TCPSocket.h"
#include "utils/ConfigParser.h"
#include "utils/ThreadPool.h"

namespace SimpleHTTPServer {
    class ApplicationServer {
    private:
        ThreadPool threadPool = ThreadPool(std::thread::hardware_concurrency());

        std::string resourceFolder = "resources/";

        const std::string GET = "GET";

        void getStaticHTMLs();
        std::unique_ptr<std::map<std::string, std::string>> staticHTMLs = nullptr;
        void getStaticHTML(const std::string &name, const std::string &htmlFile);
        static void transferFile(const int &socketFileDescriptor, const std::string &endPoint);
        static void respondBack(const int &socketFileDescriptor, const std::string &resp);
    public:
        ApplicationServer(Utils::Config config);
        void handleRequest(const int &socketFileDescriptor);
    };
}

#endif //SIMPLECPPSERVER_APPLICATIONSERVER_H
