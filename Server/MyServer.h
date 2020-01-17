//
// Created by kuribohkute on 15/01/2020.
//

#ifndef DTLMINIPROJECT_MYSERVER_H
#define DTLMINIPROJECT_MYSERVER_H

#include "Server.h"
#include "../SocketUtility/TCPSocket.h"
#include <cstring>
#include "Requests/RESTInformation.h"
#include "Requests/RESTHandler.h"
#include "Requests/RequestHandlers.h"
#include <map>
#include <fstream>

namespace ServerNS {
    class MyServer : public Server {
    private:
        const std::string resourcesFolder = "../resources/html/";
        SocketUtility::TCPSocket* tcpSocket = nullptr;
        void getStaticHTMLs();
        std::map<std::string, std::string> *staticHTMLs;
        void getStaticHTML(std::string name, std::string htmlFile);
    public:
        explicit MyServer(bool _onlyPureRequest = false);
        ~MyServer() override;
        void start();
        void handleRequest(const int &sockfd) override;
        static void respondBack(const int &sockfd, std::string &resp);
    };
}

#endif //DTLMINIPROJECT_MYSERVER_H
