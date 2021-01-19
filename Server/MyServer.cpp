
#include "MyServer.h"

#include <unistd.h>

#include <fstream>
#include <cstring>

#include "Requests/RESTInformation.h"
#include "Requests/RequestHandlers.h"
#include "ServerConstants.h"
#include "utils/OtherUtils.h"

void SimpleCPPServer::MyServer::handleRequest(const int &sockfd) {
    char buffer[SimpleCPPServer::bufferSize] = {0};

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

    auto [method, endPoint] = SimpleCPPServer::REST_INFORMATION::parseInformation(reqInfo);

    if (method == this->GET && endPoint == "/") {
        respondBack(sockfd, SimpleCPPServer::RequestHandler::getIndexPage());
        return;
    }

    std::string content = (*this->staticHTMLs)["index"];
    std::string resp = RequestHandler::resp(content);

    auto isGetStaticHTML = false;

    if (method == this->GET && endPoint == "/about") {
        content = (*this->staticHTMLs)["about"];
        resp = RequestHandler::resp(content);
        isGetStaticHTML = true;
    }
    if (isGetStaticHTML) {
        SimpleCPPServer::MyServer::respondBack(sockfd, resp);
    } else {
        if (method == this->GET) {
            endPoint = Utils::OtherUtils::normalizeString(endPoint);

            this->threadPool.enqueue([] (const int sockfd, const std::string &endPoint) {
                SimpleCPPServer::MyServer::transferFile(sockfd, endPoint);
            }, sockfd, endPoint);
        }
    }
}

SimpleCPPServer::MyServer::MyServer() {
    this->tcpSocket = std::make_unique<SimpleCPPServer::TCPSocket>();
    this->tcpSocket->initServer(std::unique_ptr<SimpleCPPServer::Server>(this));
    this->staticHTMLs = std::make_unique<std::map<std::string, std::string>>();
    this->getStaticHTMLs();
}

SimpleCPPServer::MyServer::~MyServer() = default;

void SimpleCPPServer::MyServer::start() {
    this->tcpSocket->start();
}

void SimpleCPPServer::MyServer::respondBack(const int &sockfd, const std::string &resp) {
    auto signal = write(sockfd, &*resp.begin(), strlen(&*resp.begin()));
}

void SimpleCPPServer::MyServer::getStaticHTMLs() {
    this->getStaticHTML("index", "index.html");
    this->getStaticHTML("about", "about.html");
}

void SimpleCPPServer::MyServer::getStaticHTML(const std::string &name, const std::string &htmlFile) {
    (*this->staticHTMLs)[name] = "";
    std::ifstream fi(SimpleCPPServer::resourcesFolder + htmlFile);
    std::string line;
    while (getline(fi, line)) {
        (*this->staticHTMLs)[name] += line;
    }
    fi.close();
}

void SimpleCPPServer::MyServer::transferFile(const int &sockfd, const std::string &endPoint) {
    std::string fileName;
    auto n = endPoint.size();
    for (auto i = 1; i < n; i++) {
        fileName += endPoint[i];
    }
    auto fileType = Utils::OtherUtils::getFileType(fileName);
    auto filePath = SimpleCPPServer::resourcesFolder + fileName;

    auto fileLength = Utils::OtherUtils::getFileSize(filePath);
    if (fileLength < 0) {
        auto header = SimpleCPPServer::RequestHandler::getHeader(14, fileType, 500);
        SimpleCPPServer::MyServer::respondBack(sockfd, header);
        SimpleCPPServer::MyServer::respondBack(sockfd, "File not found");
        return;
    }

    auto header = SimpleCPPServer::RequestHandler::getHeader(fileLength, fileType, 200);
    SimpleCPPServer::MyServer::respondBack(sockfd, header);

    char send_buffer[SimpleCPPServer::bufferSize];
    FILE *sendFile = fopen(filePath.c_str(), "r");
    while (sendFile && !feof(sendFile)) {
        int numRead = fread(send_buffer, sizeof(unsigned char), SimpleCPPServer::bufferSize, sendFile);
        if( numRead < 1 ) break; // EOF or error

        char *send_buffer_ptr = send_buffer;

        while (numRead > 0) {
            int numSent = write(sockfd, send_buffer_ptr, numRead);
            if (numSent < 1) {// 0 if disconnected, otherwise error
                break; // timeout or error
            }
            send_buffer_ptr += numSent;
            numRead -= numSent;
        }

    }
    fclose(sendFile);
}
