
#ifndef SIMPLECPPSERVER_REQUESTHANDLERS_H
#define SIMPLECPPSERVER_REQUESTHANDLERS_H

#include <string>

namespace SimpleCPPServer {
    class RequestHandler {
    public:
        static std::string resp(const std::string &html);
        static std::string getHeader(const int &contentLength, const std::string &fileType, const int &statusCode);
        static std::string contentType(const std::string &fileType);
        static std::string responseStatus(const int &statusCode);
        static std::string getIndexPage();
    };
}

#endif //SIMPLECPPSERVER_REQUESTHANDLERS_H
