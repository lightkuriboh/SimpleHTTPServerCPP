//
// Created by kuribohkute on 16/01/2020.
//

#ifndef DTLMINIPROJECT_REQUESTHANDLERS_H
#define DTLMINIPROJECT_REQUESTHANDLERS_H

#include <iostream>
#include "RESTHandler.h"
#include "../../utils/OtherUtils.h"

namespace ServerNS {
    class RequestHandler {
    private:
        static std::string resp(const std::string &html);
    public:
        static std::string getIndexPage();
        static std::string getAboutPage();
    };
}

#endif //DTLMINIPROJECT_REQUESTHANDLERS_H
