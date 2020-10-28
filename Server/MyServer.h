//
// Created by kuribohkute on 15/01/2020.
//

#ifndef DTLMINIPROJECT_MYSERVER_H
#define DTLMINIPROJECT_MYSERVER_H

#include <map>
#include <fstream>
#include <cstring>

#include "Server.h"
#include "ServerConstants.h"
#include "Requests/RESTInformation.h"
#include "Requests/RequestHandlers.h"

#include "../SocketUtility/TCPSocket.h"
#include "../utils/ThreadPool.h"

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
        explicit MyServer(bool _onlyPureRequest = false);
        ~MyServer() override;
        void start();
        void handleRequest(const int &sockfd) override;
    };
}

#endif //DTLMINIPROJECT_MYSERVER_H
