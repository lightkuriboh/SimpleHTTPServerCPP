
#include "RequestHandlers.h"

#include <set>

#include "utils/OtherUtils.h"

std::string SimpleHTTPServer::RequestHandler::contentType(const std::string &fileType) {
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

std::string SimpleHTTPServer::RequestHandler::resp(const std::string &html) {
    std::string result = SimpleHTTPServer::RequestHandler::getHeader(html.size(), "html", 200) + html;
    return result;
}

std::string SimpleHTTPServer::RequestHandler::responseStatus(const int &statusCode) {
    std::string ans = "200 OK\n";
    if (statusCode != 200) {

    }
    return ans;
}

std::string
SimpleHTTPServer::RequestHandler::getHeader(const int &contentLength, const std::string &fileType, const int &statusCode) {
    return "HTTP/1.1 "
           + SimpleHTTPServer::RequestHandler::responseStatus(statusCode)
           + SimpleHTTPServer::RequestHandler::contentType(fileType)
           + "Content-Length: "
           + Utils::OtherUtils::intToString(contentLength)
           + "\n\n"
        ;
}

std::string SimpleHTTPServer::RequestHandler::getIndexPage() {
    return "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 107\n\n<html><body style='color:red;text-align:center'>Hello world<br><hr><a href='/about'>About</a></body></html>";
}