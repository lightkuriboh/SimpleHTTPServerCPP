
#ifndef SIMPLECPPSERVER_RFCWRAPPER_H
#define SIMPLECPPSERVER_RFCWRAPPER_H

#include <string>

namespace LibraryWrapper {
    class RFCWrapper {
    public:
        static std::string response(const std::string &html);
        static std::string getHeader(const int &contentLength, const std::string &fileType, const int &statusCode);
        static std::string contentType(const std::string &fileType);
        static std::string responseStatus(const int &statusCode);
        static std::pair<std::string, std::string> parseRESTInformation(const std::string &requestContent);
    };
}

#endif //SIMPLECPPSERVER_RFCWRAPPER_H
