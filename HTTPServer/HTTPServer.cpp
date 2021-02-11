
#include "HTTPServer/HTTPServer.h"

#include "libs/EPollUtility.h"
#include "libs/RFCWrapper.h"
#include "libs/SocketUtility.h"
#include "libs/UnixStandardUtility.h"
#include "RESTInformation.h"
#include "utils/FileUtils.h"

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
    this->getAllStaticFiles();
}

void SimpleHTTPServer::HTTPServer::start() {
    this->listeningConnections();
}

void SimpleHTTPServer::HTTPServer::getAllStaticFiles() {
    this->getTextFileContent("index.html");
    this->getTextFileContent("about.html");
}

void SimpleHTTPServer::HTTPServer::getTextFileContent(const std::string &fileName) {
    this->staticTextContents[fileName] = "";
    std::ifstream fi(this->resourceFolder + fileName);
    std::string line;
    while (getline(fi, line)) {
        this->staticTextContents[fileName] += line;
    }
    fi.close();
}

void SimpleHTTPServer::HTTPServer::handleRequest(const int &socketFileDescriptor) {
    auto requestContent = LibraryWrapper::UnixStandard::readFromSocketFileDescriptor(
            socketFileDescriptor,
            SimpleHTTPServer::HardConfig::ioBufferSize
    );

    auto [method, endPoint] = SimpleHTTPServer::REST_INFORMATION::parseInformation(requestContent);

    if (method == "GET") {
        if (endPoint == "/") {
            LibraryWrapper::UnixStandard::writeToSockFd(
                    socketFileDescriptor,
                    RFCWrapper::resp(this->staticTextContents["index.html"])
            );
            return;
        }
        if (auto filePath = endPoint.substr(1, (int)endPoint.length() - 1);
            this->staticTextContents.find(filePath) != this->staticTextContents.end()) {
            LibraryWrapper::UnixStandard::writeToSockFd(
                    socketFileDescriptor,
                    RFCWrapper::resp(this->staticTextContents[filePath])
            );
            return;
        }
        if (Utils::FileUtils::isFilePath(endPoint)) {
            this->threadPool.enqueue([this] (const int socketFileDescriptor, const std::string &endPoint) {
                SimpleHTTPServer::HTTPServer::transferFile(socketFileDescriptor,
                                                           this->resourceFolder + endPoint.substr(
                                                                   1, (int)endPoint.length() - 1)
                                                           );
            }, socketFileDescriptor, endPoint);
            return;
        }
    }
}

void SimpleHTTPServer::HTTPServer::transferFile(const int &socketFileDescriptor, const std::string &filePath) {
    auto fileType = Utils::FileUtils::getFileType(filePath);

    auto fileLength = Utils::FileUtils::getFileSize(filePath);
    if (fileLength < 0) {
        auto header = SimpleHTTPServer::RFCWrapper::getHeader(14, fileType, 500);
        LibraryWrapper::UnixStandard::writeToSockFd(socketFileDescriptor, header);
        LibraryWrapper::UnixStandard::writeToSockFd(socketFileDescriptor, "File not found");
        return;
    }

    auto header = SimpleHTTPServer::RFCWrapper::getHeader(fileLength, fileType, 200);
    LibraryWrapper::UnixStandard::writeToSockFd(socketFileDescriptor, header);

    char send_buffer[SimpleHTTPServer::HardConfig::ioBufferSize];
    std::unique_ptr<FILE> sendFile(fopen(filePath.c_str(), "r"));

    while (sendFile && !feof(sendFile.get())) {
        int numRead = fread(
                send_buffer,
                sizeof(unsigned char),
                SimpleHTTPServer::HardConfig::ioBufferSize, sendFile.get()
        );
        if (numRead <= 0) break;

        auto send_buffer_ptr = send_buffer;

        while (numRead > 0) {
            int numSent = LibraryWrapper::UnixStandard::writeToSockFd(socketFileDescriptor, send_buffer_ptr, numRead);
            if (numSent <= 1) {
                break;
            }
            send_buffer_ptr += numSent;
            numRead -= numSent;
        }
    }
}

