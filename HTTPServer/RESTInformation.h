
#ifndef SIMPLECPPSERVER_RESTINFORMATION_H
#define SIMPLECPPSERVER_RESTINFORMATION_H

#include <string>

namespace SimpleHTTPServer {
    struct REST_INFORMATION {
        std::string method;
        std::string endPoint;
        REST_INFORMATION(std::string method, std::string endPoint):
            method{std::move(method)},
            endPoint(std::move(endPoint))
            {}
        static REST_INFORMATION parseInformation(const std::string &requestContent);
    };
}

#endif //SIMPLECPPSERVER_RESTINFORMATION_H
