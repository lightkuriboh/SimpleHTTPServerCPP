//
// Created by kuribohkute on 15/01/2020.
//

#ifndef DTLMINIPROJECT_SIGNALHANDLER_H
#define DTLMINIPROJECT_SIGNALHANDLER_H

#include <csignal>
#include <iostream>
#include <unistd.h>
#include "../constants.h"

namespace Signals {
    void keyboardInterruptHandler(int signalNumber);
    void setSignalHandlers();
}

#endif //DTLMINIPROJECT_SIGNALHANDLER_H
