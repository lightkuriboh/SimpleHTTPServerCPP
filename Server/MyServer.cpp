//
// Created by kuribohkute on 15/01/2020.
//

#include "MyServer.h"

void ServerNS::MyServer::handleRequest(const int &sockfd) {
    char buffer[SocketUtility::bufferSize] = {0};

    auto readValue = read(sockfd, buffer, sizeof(buffer));

    if (readValue <= 0) {
        return;
    }

    std::string reqInfo;
    for (auto i = 0; i < readValue; ++i) {
        if (buffer[i] == '\n') {
            break;
        }
        reqInfo += buffer[i];
    }

    auto [method, endPoint] = ServerNS::REST_INFORMATION::parseInformation(reqInfo);
//    std::cout << method + ' ' + endPoint << std::endl;
    if (method == "GET" && endPoint == "/") {
        std::string resp = RequestHandler::getIndexPage();
        respondBack(sockfd, resp);
    } else
        if (method == "GET" && endPoint == "/about") {
            std::string resp = RequestHandler::getAboutPage();
            respondBack(sockfd, resp);
        } else
            if (method == "GET" && endPoint == "/favicon.ico") {
                std::string resp = RequestHandler::getIndexPage();
                respondBack(sockfd, resp);
            }

//    std::string hello = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 55\n\n<html><body style='color:red'>Hello world</body></html>";
//    respondBack(sockfd, hello);
}

ServerNS::MyServer::MyServer(bool _onlyPureRequest) {
    this->tcpSocket = new SocketUtility::TCPSocket();
    this->tcpSocket->initServer(this);
    this->setOnlyPureRequest(_onlyPureRequest);
}

ServerNS::MyServer::~MyServer() {
    delete tcpSocket;
}

void ServerNS::MyServer::start() {
    this->tcpSocket->start();
}

void ServerNS::MyServer::respondBack(const int &sockfd, std::string &resp) {
    auto signal = write(sockfd, &*resp.begin(), strlen(&*resp.begin()));
}
