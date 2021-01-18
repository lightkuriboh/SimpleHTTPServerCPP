//
// Created by kuribohkute on 16/01/2020.
//

#ifndef SIMPLECPPSERVER_REQUESTHANDLERS_H
#define SIMPLECPPSERVER_REQUESTHANDLERS_H

#include <set>
#include <iostream>

#include "../../utils/OtherUtils.h"

namespace ServerNS {
    class RequestHandler {
    public:
        static std::string resp(const std::string &html);
        static std::string getHeader(const int &contentLength, const std::string &fileType, const int &statusCode);
        static std::string contentType(const std::string &fileType);
        static std::string responseStatus(const int &statusCode);
        static std::string getIndexPage();
    };
}

#endif //SIMPLECPPSERVER_REQUESTHANDLERS_H
