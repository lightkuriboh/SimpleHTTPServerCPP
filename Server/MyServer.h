//
// Created by kuribohkute on 15/01/2020.
//

#ifndef SIMPLECPPSERVER_MYSERVER_H
#define SIMPLECPPSERVER_MYSERVER_H

#include <cstring>
#include <fstream>
#include <map>

#include "Requests/RESTInformation.h"
#include "Requests/RequestHandlers.h"
#include "Server.h"
#include "ServerConstants.h"
#include "SocketUtility/TCPSocket.h"
#include "utils/ThreadPool.h"

namespace ServerNS {
    class MyServer : public Server {
    private:
        ThreadPool threadPool = ThreadPool(std::thread::hardware_concurrency());

        const std::string GET = "GET";

        std::unique_ptr<SocketUtility::TCPSocket> tcpSocket = nullptr;
        void getStaticHTMLs();
        std::unique_ptr<std::map<std::string, std::string>> staticHTMLs = nullptr;
        void getStaticHTML(const std::string &name, const std::string &htmlFile);
        static void transferFile(const int &sockfd, const std::string &endPoint);
        static void respondBack(const int &sockfd, const std::string &resp);
    public:
        MyServer();
        ~MyServer() override;
        void start();
        void handleRequest(const int &sockfd) override;
    };
}

#endif //SIMPLECPPSERVER_MYSERVER_H
