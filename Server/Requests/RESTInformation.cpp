
#include "RESTInformation.h"

SimpleHTTPServer::REST_INFORMATION SimpleHTTPServer::REST_INFORMATION::parseInformation(const std::string &info) {
    std::string method, endPoint;
    auto methodSet = false;
    for (const auto &ch: info) {
        if (ch == ' ') {
            if (!methodSet) {
                methodSet = true;
            } else {
                break;
            }
        } else {
            if (!methodSet) {
                method += ch;
            } else {
                endPoint += ch;
            }
        }
    }
    return SimpleHTTPServer::REST_INFORMATION (method, endPoint);
}

SimpleHTTPServer::REST_INFORMATION::REST_INFORMATION(const std::string &_method, const std::string &_endPoint) {
    this->method = _method;
    this->endPoint = _endPoint;
}
