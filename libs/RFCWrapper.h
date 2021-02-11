
#ifndef SIMPLECPPSERVER_RFCWRAPPER_H
#define SIMPLECPPSERVER_RFCWRAPPER_H

#include <string>

namespace SimpleHTTPServer {
    class RequestHandler {
    public:
        static std::string resp(const std::string &html);
        static std::string getHeader(const int &contentLength, const std::string &fileType, const int &statusCode);
        static std::string contentType(const std::string &fileType);
        static std::string responseStatus(const int &statusCode);
    };
}

#endif //SIMPLECPPSERVER_RFCWRAPPER_H
