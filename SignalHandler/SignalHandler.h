//
// Created by kuribohkute on 15/01/2020.
//

#ifndef SIMPLECPPSERVER_SIGNALHANDLER_H
#define SIMPLECPPSERVER_SIGNALHANDLER_H

#include <csignal>
#include <iostream>
#include <unistd.h>
#include "../constants.h"

namespace Signals {
    void keyboardInterruptHandler(int signalNumber);
    void setSignalHandlers();
}

#endif //SIMPLECPPSERVER_SIGNALHANDLER_H
