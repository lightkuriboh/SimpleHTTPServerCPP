
#include "RESTInformation.h"

#include "utils/CommonUtils.h"

SimpleHTTPServer::REST_INFORMATION
SimpleHTTPServer::REST_INFORMATION::parseInformation(const std::string &requestContent) {
    std::string method, endPoint;
    auto methodSet = false;
    for (const auto &ch: requestContent) {
        if (ch == '\n') {
            break;
        }
        if (ch == ' ') {
            if (!methodSet) {
                methodSet = true;
            } else {
                break;
            }
        } else {
            if (!methodSet) {
                method += ch;
            } else {
                endPoint += ch;
            }
        }
    }
    return SimpleHTTPServer::REST_INFORMATION (method, Utils::CommonUtils::normalizeString(endPoint));
}
