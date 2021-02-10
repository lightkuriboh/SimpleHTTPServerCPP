
#include "HTTPServer/HTTPServer.h"

#include "unistd.h"

#include <fstream>

#include "libs/EPollUtility.h"
#include "libs/SocketUtility.h"
#include "libs/UnixStandardUtility.h"
#include "ApplicationServer/Requests/RESTInformation.h"
#include "ApplicationServer/Requests/RequestHandlers.h"
#include "ApplicationServer/ServerConstants.h"
#include "utils/OtherUtils.h"

ReturnStatus SimpleHTTPServer::HTTPServer::listeningConnections() {
    this->addNewConnection(this->myTcpSocket.getSocketMaster());
    while (true) {
        int numberFDs = LibraryWrapper::EPoll::getChangedEPollEvents(this->epollContext, this->epollEvents);
        for (int i = 0; i < numberFDs; ++i) {
            auto socketFileDescriptor = this->epollEvents[i].data.fd;
            if (this->isSocketMaster(socketFileDescriptor)) {
                int newSocket = LibraryWrapper::Socket::acceptNewConnection(
                this->myTcpSocket.getSocketMaster()
                );

                if (LibraryWrapper::Socket::createSocketSuccessfully(newSocket)) {
                    this->addNewConnection(newSocket);
                } else {
                    perror("Error accepting new connection!");
                    return ReturnStatus::FAILURE;
                }
            } else {
                if (LibraryWrapper::EPoll::errorOccurredWithEPollEvent(this->epollEvents[i])
                    ||
                    LibraryWrapper::EPoll::clientClosedTheConnection(this->epollEvents[i])) {

                    this->closeConnection(socketFileDescriptor);
                } else {
                    this->handleRequest(socketFileDescriptor);
                }
            }
        }
    }
}

void SimpleHTTPServer::HTTPServer::closeConnection(const int &socketFileDescriptor) const {
    LibraryWrapper::EPoll::removeFromEpoll(this->epollContext, socketFileDescriptor);
    LibraryWrapper::UnixStandard::closeFileDescriptor(socketFileDescriptor);
}

void SimpleHTTPServer::HTTPServer::addNewConnection(const int &socketFileDescriptor) const {
    LibraryWrapper::EPoll::addToEpoll(this->epollContext, socketFileDescriptor);
}

SimpleHTTPServer::HTTPServer::HTTPServer() {
    this->epollEvents.resize(this->config.getMaximumConnections() + 1);
    this->epollContext = LibraryWrapper::EPoll::creatEPollContext(this->config.getMaximumConnections() + 1);
    this->resourceFolder = this->config.getResourceFolder();
    this->getAllStaticHTMLs();
}

void SimpleHTTPServer::HTTPServer::start() {
    this->listeningConnections();
}

void SimpleHTTPServer::HTTPServer::getAllStaticHTMLs() {
    this->getStaticHTML("index", "index.html");
    this->getStaticHTML("about", "about.html");
}

void SimpleHTTPServer::HTTPServer::getStaticHTML(const std::string &name, const std::string &htmlFile) {
    this->staticHTMLs[name] = "";
    std::ifstream fi(this->resourceFolder + htmlFile);
    std::string line;
    while (getline(fi, line)) {
        this->staticHTMLs[name] += line;
    }
    fi.close();
}

void SimpleHTTPServer::HTTPServer::handleRequest(const int &socketFileDescriptor) {
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

    if (method == "GET" && endPoint == "/") {
        LibraryWrapper::UnixStandard::writeToSockFd(
                socketFileDescriptor,
                SimpleHTTPServer::RequestHandler::getIndexPage()
        );
        return;
    }

    std::string content = this->staticHTMLs["index"];
    std::string resp = RequestHandler::resp(content);

    auto isGetStaticHTML = false;

    if (method == "GET" && endPoint == "/about") {
        content = this->staticHTMLs["about"];
        resp = RequestHandler::resp(content);
        isGetStaticHTML = true;
    }
    if (isGetStaticHTML) {
        LibraryWrapper::UnixStandard::writeToSockFd(
                socketFileDescriptor,
                resp
        );
    } else {
        if (method == "GET") {
            endPoint = Utils::OtherUtils::normalizeString(endPoint);

            this->threadPool.enqueue([] (const int socketFileDescriptor, const std::string &endPoint) {
                SimpleHTTPServer::HTTPServer::transferFile(socketFileDescriptor, endPoint);
            }, socketFileDescriptor, endPoint);
        }
    }
}

void SimpleHTTPServer::HTTPServer::transferFile(const int &socketFileDescriptor, const std::string &endPoint) {
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
        LibraryWrapper::UnixStandard::writeToSockFd(socketFileDescriptor, header);
        LibraryWrapper::UnixStandard::writeToSockFd(socketFileDescriptor, "File not found");
        return;
    }

    auto header = SimpleHTTPServer::RequestHandler::getHeader(fileLength, fileType, 200);
    LibraryWrapper::UnixStandard::writeToSockFd(socketFileDescriptor, header);

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

