
#ifndef SIMPLECPPSERVER_RESTINFORMATION_H
#define SIMPLECPPSERVER_RESTINFORMATION_H

#include <string>

namespace ServerNS {
    struct REST_INFORMATION {
        std::string method;
        std::string endPoint;
        REST_INFORMATION(const std::string &_method, const std::string &_endPoint);
        static REST_INFORMATION parseInformation(const std::string &info);
    };
}

#endif //SIMPLECPPSERVER_RESTINFORMATION_H
