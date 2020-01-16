//
// Created by kuribohkute on 16/01/2020.
//

#include "RESTHandler.h"

std::string ServerNS::RESTHandler::handle(REST_INFORMATION &info) {
    return this->processREST(info);
}

ServerNS::RESTHandler::RESTHandler(std::string (*_processREST)(REST_INFORMATION&)) {
    this->processREST = _processREST;
}

