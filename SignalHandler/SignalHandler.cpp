//
// Created by kuribohkute on 15/01/2020.
//

#include "SignalHandler.h"

void Signals::setSignalHandlers() {
    signal(SIGINT, keyboardInterruptHandler);
}

void Signals::keyboardInterruptHandler(int signalNumber) {
    close(SocketUtility::PORT);
    exit(signalNumber);
}

