//
// Created by kuribohkute on 16/01/2020.
//

#include "RESTInformation.h"

ServerNS::REST_INFORMATION ServerNS::REST_INFORMATION::parseInformation(const std::string &info) {
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
    return ServerNS::REST_INFORMATION (method, endPoint);
}

ServerNS::REST_INFORMATION::REST_INFORMATION(const std::string &_method, const std::string &_endPoint) {
    this->method = _method;
    this->endPoint = _endPoint;
}
