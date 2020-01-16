//
// Created by kuribohkute on 16/01/2020.
//

#ifndef DTLMINIPROJECT_RESTINFORMATION_H
#define DTLMINIPROJECT_RESTINFORMATION_H

#include <cstring>
#include <iostream>

namespace ServerNS {
    struct REST_INFORMATION {
        std::string method;
        std::string endPoint;
        REST_INFORMATION(const std::string &_method, const std::string &_endPoint);
        static REST_INFORMATION parseInformation(const std::string &info);
    };
}

#endif //DTLMINIPROJECT_RESTINFORMATION_H
