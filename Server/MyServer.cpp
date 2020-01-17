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

    std::string content;
    std::string resp;

    if (method == "GET" && endPoint == "/") {
        content = (*this->staticHTMLs)["index"];
        resp = RequestHandler::resp(content);
    } else
        if (method == "GET" && endPoint == "/about") {
            content = (*this->staticHTMLs)["about"];
            resp = RequestHandler::resp(content);
        } else
            if (method == "GET" && endPoint == "/favicon.ico") {
                content = (*this->staticHTMLs)["index"];
                resp = RequestHandler::resp(content);
            }

    respondBack(sockfd, resp);
}

ServerNS::MyServer::MyServer(bool _onlyPureRequest) {
    this->tcpSocket = new SocketUtility::TCPSocket();
    this->tcpSocket->initServer(this);
    this->setOnlyPureRequest(_onlyPureRequest);
    this->staticHTMLs = new std::map<std::string, std::string>();
    this->getStaticHTMLs();
}

ServerNS::MyServer::~MyServer() {
    delete this->tcpSocket;
    delete this->staticHTMLs;
}

void ServerNS::MyServer::start() {
    this->tcpSocket->start();
}

void ServerNS::MyServer::respondBack(const int &sockfd, std::string &resp) {
    auto signal = write(sockfd, &*resp.begin(), strlen(&*resp.begin()));
}

void ServerNS::MyServer::getStaticHTMLs() {
    this->getStaticHTML("index", "index.html");
    this->getStaticHTML("about", "about.html");
}

void ServerNS::MyServer::getStaticHTML(std::string name, std::string htmlFile) {
    (*this->staticHTMLs)[name] = "";
    std::ifstream fi;
    fi.open(this->resourcesFolder + htmlFile);
    std::string line;
    while (getline(fi, line)) {
        (*this->staticHTMLs)[name] += line;
    }
    fi.close();
}
