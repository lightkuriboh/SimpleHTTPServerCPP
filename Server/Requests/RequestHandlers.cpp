//
// Created by kuribohkute on 16/01/2020.
//

#include "RequestHandlers.h"

std::string ServerNS::RequestHandler::getIndexPage() {
    std::string html = "<html><body style='color:red'>Hello world<br><a href='/about'>About</a></body></html>";
    return ServerNS::RequestHandler::resp(html);
}

std::string ServerNS::RequestHandler::getAboutPage() {
    std::string html = "<html><body style='color:red'><a href='/'>Home</a><br><a href='https://www.facebook.com/phamngoc.hieu.161' target='_blank'>HieuPro</a></body></html>";
    return ServerNS::RequestHandler::resp(html);
}

std::string ServerNS::RequestHandler::resp(const std::string &html) {
    std::string header = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: ";
    std::string result = header + Utils::OtherUtils::intToString((int)html.size()) + "\n\n" + html;
    return result;
}

