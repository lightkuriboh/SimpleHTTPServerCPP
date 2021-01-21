
#include "ApplicationServer.h"

#include <unistd.h>

#include <fstream>
#include <cstring>

#include "Requests/RESTInformation.h"
#include "Requests/RequestHandlers.h"
#include "ServerConstants.h"
#include "utils/OtherUtils.h"

void SimpleHTTPServer::ApplicationServer::handleRequest(const int &socketFileDescriptor) {
    char buffer[SimpleHTTPServer::bufferSize] = {0};

    auto readValue = read(socketFileDescriptor, buffer, sizeof(buffer));

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

    auto [method, endPoint] = SimpleHTTPServer::REST_INFORMATION::parseInformation(reqInfo);

    if (method == this->GET && endPoint == "/") {
        respondBack(socketFileDescriptor, SimpleHTTPServer::RequestHandler::getIndexPage());
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
        SimpleHTTPServer::ApplicationServer::respondBack(socketFileDescriptor, resp);
    } else {
        if (method == this->GET) {
            endPoint = Utils::OtherUtils::normalizeString(endPoint);

            this->threadPool.enqueue([] (const int socketFileDescriptor, const std::string &endPoint) {
                SimpleHTTPServer::ApplicationServer::transferFile(socketFileDescriptor, endPoint);
            }, socketFileDescriptor, endPoint);
        }
    }
}

SimpleHTTPServer::ApplicationServer::ApplicationServer(Utils::Config config) {
    this->resourceFolder = config.getResourceFolder();
    this->staticHTMLs = std::make_unique<std::map<std::string, std::string>>();
    this->getStaticHTMLs();
}

void SimpleHTTPServer::ApplicationServer::respondBack(const int &sockfd, const std::string &resp) {
    auto signal = write(sockfd, &*resp.begin(), strlen(&*resp.begin()));
}

void SimpleHTTPServer::ApplicationServer::getStaticHTMLs() {
    this->getStaticHTML("index", "index.html");
    this->getStaticHTML("about", "about.html");
}

void SimpleHTTPServer::ApplicationServer::getStaticHTML(const std::string &name, const std::string &htmlFile) {
    (*this->staticHTMLs)[name] = "";
    std::ifstream fi(this->resourceFolder + htmlFile);
    std::string line;
    while (getline(fi, line)) {
        (*this->staticHTMLs)[name] += line;
    }
    fi.close();
}

void SimpleHTTPServer::ApplicationServer::transferFile(const int &socketFileDescriptor, const std::string &endPoint) {
    std::string fileName;
    auto n = endPoint.size();
    for (auto i = 1; i < n; i++) {
        fileName += endPoint[i];
    }
    auto fileType = Utils::OtherUtils::getFileType(fileName);
    auto filePath = SimpleHTTPServer::resourcesFolder + fileName;

    auto fileLength = Utils::OtherUtils::getFileSize(filePath);
    if (fileLength < 0) {
        auto header = SimpleHTTPServer::RequestHandler::getHeader(14, fileType, 500);
        SimpleHTTPServer::ApplicationServer::respondBack(socketFileDescriptor, header);
        SimpleHTTPServer::ApplicationServer::respondBack(socketFileDescriptor, "File not found");
        return;
    }

    auto header = SimpleHTTPServer::RequestHandler::getHeader(fileLength, fileType, 200);
    SimpleHTTPServer::ApplicationServer::respondBack(socketFileDescriptor, header);

    char send_buffer[SimpleHTTPServer::bufferSize];
    FILE *sendFile = fopen(filePath.c_str(), "r");
    while (sendFile && !feof(sendFile)) {
        int numRead = fread(send_buffer, sizeof(unsigned char), SimpleHTTPServer::bufferSize, sendFile);
        if( numRead < 1 ) break; // EOF or error

        char *send_buffer_ptr = send_buffer;

        while (numRead > 0) {
            int numSent = write(socketFileDescriptor, send_buffer_ptr, numRead);
            if (numSent < 1) {// 0 if disconnected, otherwise error
                break; // timeout or error
            }
            send_buffer_ptr += numSent;
            numRead -= numSent;
        }

    }
    fclose(sendFile);
}
