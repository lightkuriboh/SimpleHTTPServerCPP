//
// Created by kuribohkute on 16/01/2020.
//

#include "Server.h"

bool ServerNS::Server::getOnlyPureRequest() {
    return this->onlyPureRequest;
}

void ServerNS::Server::setOnlyPureRequest(bool _onlyPureRequest) {
    this->onlyPureRequest = _onlyPureRequest;
}

