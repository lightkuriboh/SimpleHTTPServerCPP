
#include "SignalHandler.h"

#include <unistd.h>

#include <csignal>
#include <iostream>

#include "constants.h"

void Signals::setSignalHandlers() {
    signal(SIGINT, keyboardInterruptHandler);
}

void Signals::keyboardInterruptHandler(int signalNumber) {
    close(SimpleHTTPServer::PORT);
    exit(signalNumber);
}

