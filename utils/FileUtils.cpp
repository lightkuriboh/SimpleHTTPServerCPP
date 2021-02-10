//
// Created by kuribohkute on 10/02/2021.
//

#include "FileUtils.h"

#include "ApplicationServer/Requests/RequestHandlers.h"
#include "libs/UnixStandardUtility.h"
#include "utils/OtherUtils.h"

void Utils::FileUtils::transferFile(const int &socketFileDescriptor, const std::string &filePath) {
    auto fileType = Utils::OtherUtils::getFileType(filePath);

    auto fileLength = Utils::OtherUtils::getFileSize(filePath);
    if (fileLength < 0) {
        auto header = SimpleHTTPServer::RequestHandler::getHeader(14, fileType, 500);
        LibraryWrapper::UnixStandard::writeToSockFd(socketFileDescriptor, header);
        LibraryWrapper::UnixStandard::writeToSockFd(socketFileDescriptor, "File not found");
        return;
    }

    auto header = SimpleHTTPServer::RequestHandler::getHeader(fileLength, fileType, 200);
    LibraryWrapper::UnixStandard::writeToSockFd(socketFileDescriptor, header);

    char send_buffer[2048];
    FILE *sendFile = fopen(filePath.c_str(), "r");
    while (sendFile && !feof(sendFile)) {
        int numRead = fread(send_buffer, sizeof(unsigned char), 2048, sendFile);
        if( numRead < 1 ) break; // EOF or error

        char *send_buffer_ptr = send_buffer;

        while (numRead > 0) {
            int numSent = LibraryWrapper::UnixStandard::writeToSockFd(socketFileDescriptor, send_buffer_ptr, numRead);
            if (numSent < 1) {// 0 if disconnected, otherwise error
                break; // timeout or error
            }
            send_buffer_ptr += numSent;
            numRead -= numSent;
        }
    }
    fclose(sendFile);
}

