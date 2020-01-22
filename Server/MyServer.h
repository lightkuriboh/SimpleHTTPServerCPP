//
// Created by kuribohkute on 15/01/2020.
//

#ifndef DTLMINIPROJECT_MYSERVER_H
#define DTLMINIPROJECT_MYSERVER_H

#include <map>
#include <fstream>
#include <cstring>

#include "Server.h"
#include "../utils/ThreadPool.h"
#include "Requests/RESTInformation.h"
#include "Requests/RequestHandlers.h"
#include "../SocketUtility/TCPSocket.h"

namespace ServerNS {
    const std::string resourcesFolder = "resources/";
    class MyServer : public Server {
    private:
        ThreadPool threadPool = ThreadPool(std::thread::hardware_concurrency());

        const std::string GET = "GET";

        SocketUtility::TCPSocket* tcpSocket = nullptr;
        void getStaticHTMLs();
        std::map<std::string, std::string> *staticHTMLs;
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
