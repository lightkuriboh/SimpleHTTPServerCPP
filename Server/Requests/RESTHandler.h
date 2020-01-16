//
// Created by kuribohkute on 16/01/2020.
//

#ifndef DTLMINIPROJECT_RESTHANDLER_H
#define DTLMINIPROJECT_RESTHANDLER_H

#include "RESTInformation.h"

namespace ServerNS {
    class RESTHandler {
    private:
        std::string (*processREST)(REST_INFORMATION&);
    public:
        explicit RESTHandler(std::string (*_processREST)(REST_INFORMATION&));
        std::string handle(REST_INFORMATION&);
    };
}

#endif //DTLMINIPROJECT_RESTHANDLER_H
