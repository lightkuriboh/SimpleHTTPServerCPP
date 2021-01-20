
#ifndef SIMPLECPPSERVER_MYSERVER_H
#define SIMPLECPPSERVER_MYSERVER_H

#include <map>

#include "Server.h"
#include "HTTPServer/TCPSocket.h"
#include "utils/ThreadPool.h"

namespace SimpleHTTPServer {
    class MyServer : public Server {
    private:
        ThreadPool threadPool = ThreadPool(std::thread::hardware_concurrency());

        const std::string GET = "GET";

        void getStaticHTMLs();
        std::unique_ptr<std::map<std::string, std::string>> staticHTMLs = nullptr;
        void getStaticHTML(const std::string &name, const std::string &htmlFile);
        static void transferFile(const int &sockfd, const std::string &endPoint);
        static void respondBack(const int &sockfd, const std::string &resp);
    public:
        MyServer();
        void handleRequest(const int &sockfd) override;
    };
}

#endif //SIMPLECPPSERVER_MYSERVER_H
