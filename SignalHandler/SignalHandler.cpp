//
// Created by kuribohkute on 15/01/2020.
//

#include "SignalHandler.h"

void Signals::SignalHandler::setSignalHanders() {
    signal(SIGPIPE, SIG_IGN);
}

