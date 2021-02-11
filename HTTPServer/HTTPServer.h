
#ifndef SIMPLECPPSERVER_HTTPSERVER_H
#define SIMPLECPPSERVER_HTTPSERVER_H

#include <sys/epoll.h>

#include <vector>

#include "HTTPServer/TCPSocket.h"
#include "utils/ConfigParser.h"
#include "utils/ThreadPool.h"
#include "utils/ReturnStatus.h"

namespace SimpleHTTPServer {
    class HTTPServer {
    private:
        Utils::Config config = Utils::Config();
        TCPSocket myTcpSocket = SimpleHTTPServer::TCPSocket(config);
        ThreadPool threadPool = ThreadPool(std::thread::hardware_concurrency());

        std::vector<epoll_event> epollEvents;
        int epollContext = 0;

        std::string resourceFolder = "resources/";
        void getAllStaticFiles();
        std::map<std::string, std::string> staticTextContents;
        void getTextFileContent(const std::string &fileName);

        void handleRequest(const int &socketFileDescriptor);

        void addNewConnection(const int &socketFileDescriptor) const;
        void closeConnection(const int &socketFileDescriptor) const;

        [[nodiscard]] bool isSocketMaster(const int &socketFileDescriptor) const {
            return socketFileDescriptor == this->myTcpSocket.getSocketMaster();
        }

        static void transferFile(const int &socketFileDescriptor, const std::string &filePath);
    public:
        ReturnStatus listeningConnections();

        HTTPServer();
        void start();
    };
}

#endif //SIMPLECPPSERVER_HTTPSERVER_H
