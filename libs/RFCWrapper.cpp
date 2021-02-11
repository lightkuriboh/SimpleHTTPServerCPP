
#include "RFCWrapper.h"

#include <set>

std::string SimpleHTTPServer::RFCWrapper::contentType(const std::string &fileType) {
    std::string ans = "Content-Type: ";

    std::set<std::string> textFiles = {"html", "css", "js"};
    std::set<std::string> imageFiles = {"jpg", "png", "jpeg", "ico"};

    std::string type = "text/html";

    if (textFiles.find(fileType) != textFiles.end()) {
        if (fileType == "js") {
            type = "text/javascript";
        } else {
            type = "text/" + fileType;
        }
    } else {
        if (imageFiles.find(fileType) != imageFiles.end()) {
            type = "image/" + fileType;
        }
    }
    ans += type + "\n";
    return ans;
}

std::string SimpleHTTPServer::RFCWrapper::resp(const std::string &html) {
    std::string result = SimpleHTTPServer::RFCWrapper::getHeader(html.size(), "html", 200) + html;
    return result;
}

std::string SimpleHTTPServer::RFCWrapper::responseStatus(const int &statusCode) {
    std::string ans = "200 OK\n";
    if (statusCode != 200) {}
    return ans;
}

std::string
SimpleHTTPServer::RFCWrapper::getHeader(const int &contentLength, const std::string &fileType, const int &statusCode) {
    return "HTTP/1.1 "
           + SimpleHTTPServer::RFCWrapper::responseStatus(statusCode)
           + SimpleHTTPServer::RFCWrapper::contentType(fileType)
           + "Content-Length: "
           + std::to_string(contentLength)
           + "\n\n"
        ;
}
