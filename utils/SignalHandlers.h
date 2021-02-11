
#ifndef SIMPLECPPSERVER_SIGNALHANDLERS_H
#define SIMPLECPPSERVER_SIGNALHANDLERS_H

#include <csignal>

class SignalHandlers {
private:
    static void handleBrokenPipe() {
        signal(SIGPIPE, SIG_IGN);
    }
public:
    static void setSignalHandlers() {
        SignalHandlers::handleBrokenPipe();
    }
};

#endif //SIMPLECPPSERVER_SIGNALHANDLERS_H
