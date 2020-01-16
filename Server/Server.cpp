//
// Created by kuribohkute on 16/01/2020.
//

#include "Server.h"

bool Server::Server::getOnlyPureRequest() {
    return this->onlyPureRequest;
}

void Server::Server::setOnlyPureRequest(bool _onlyPureRequest) {
    this->onlyPureRequest = _onlyPureRequest;
}

