
#ifndef SIMPLECPPSERVER_SERVER_H
#define SIMPLECPPSERVER_SERVER_H

namespace SimpleCPPServer {
    class Server {
    public:
        virtual ~Server() = default;
        virtual void handleRequest(const int &sockfd) = 0;
    };
};

#endif //SIMPLECPPSERVER_SERVER_H
