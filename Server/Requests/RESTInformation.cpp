
#include "RESTInformation.h"

SimpleCPPServer::REST_INFORMATION SimpleCPPServer::REST_INFORMATION::parseInformation(const std::string &info) {
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
    return SimpleCPPServer::REST_INFORMATION (method, endPoint);
}

SimpleCPPServer::REST_INFORMATION::REST_INFORMATION(const std::string &_method, const std::string &_endPoint) {
    this->method = _method;
    this->endPoint = _endPoint;
}
