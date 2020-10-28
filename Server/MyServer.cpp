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

    if (method == this->GET && endPoint == "/") {
        respondBack(sockfd, ServerNS::RequestHandler::getIndexPage());
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
        ServerNS::MyServer::respondBack(sockfd, resp);
    } else {
        if (method == this->GET) {
            endPoint = Utils::OtherUtils::normalizeString(endPoint);
//            std::cout << "Required endpoint" << endPoint << std::endl;
            this->threadPool.enqueue([] (const int &sockfd, const std::string &endPoint) {
                ServerNS::MyServer::transferFile(sockfd, endPoint);
            }, sockfd, endPoint);
        }
    }
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

void ServerNS::MyServer::respondBack(const int &sockfd, const std::string &resp) {
    auto signal = write(sockfd, &*resp.begin(), strlen(&*resp.begin()));
}

void ServerNS::MyServer::getStaticHTMLs() {
    this->getStaticHTML("index", "index.html");
    this->getStaticHTML("about", "about.html");
}

void ServerNS::MyServer::getStaticHTML(const std::string &name, const std::string &htmlFile) {
    (*this->staticHTMLs)[name] = "";
    std::ifstream fi;
    fi.open(ServerNS::resourcesFolder + htmlFile);
    std::string line;
    while (getline(fi, line)) {
        (*this->staticHTMLs)[name] += line;
    }
    fi.close();
}

void ServerNS::MyServer::transferFile(const int &sockfd, const std::string &endPoint) {
    std::string fileName;
    auto n = endPoint.size();
    for (auto i = 1; i < n; i++) {
        fileName += endPoint[i];
    }
    auto fileType = Utils::OtherUtils::getFileType(fileName);
    auto filePath = ServerNS::resourcesFolder + fileName;

    auto fileLength = Utils::OtherUtils::getFileSize(filePath);
    if (fileLength < 0) {
        std::cout << "File does not exist" << "\n";
        // file does not exist
        return;
    }

    auto header = ServerNS::RequestHandler::getHeader(fileLength, fileType, 200);
    ServerNS::MyServer::respondBack(sockfd, header);

    char send_buffer[SocketUtility::bufferSize];
    FILE *sendFile = fopen(filePath.c_str(), "r");
    while (sendFile && !feof(sendFile)) {
        int numRead = fread(send_buffer, sizeof(unsigned char), SocketUtility::bufferSize, sendFile);
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
