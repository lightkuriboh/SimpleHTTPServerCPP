
#include "RFCWrapper.h"

#include <set>

#include "utils/CommonUtils.h"

std::string LibraryWrapper::RFCWrapper::contentType(const std::string &fileType) {
    std::string ans = "Content-Type: ";

    std::set<std::string> textFiles = {"html", "css", "js"};
    std::set<std::string> imageFiles = {"jpg", "png", "jpeg", "ico"};

    std::string type = "text/html";

    if (textFiles.find(fileType) != textFiles.end()) {
        if (fileType == "js") {
            type = "text/javascript";
        } else {
            type = "text/" + fileType;
        }
    } else {
        if (imageFiles.find(fileType) != imageFiles.end()) {
            type = "image/" + fileType;
        }
    }
    ans += type + "\n";
    return ans;
}

std::string LibraryWrapper::RFCWrapper::response(const std::string &html) {
    std::string result = LibraryWrapper::RFCWrapper::getHeader(html.size(), "html", 200) + html;
    return result;
}

std::string LibraryWrapper::RFCWrapper::responseStatus(const int &statusCode) {
    std::string ans = "200 OK\n";
    if (statusCode != 200) {}
    return ans;
}

std::string
LibraryWrapper::RFCWrapper::getHeader(const int &contentLength, const std::string &fileType, const int &statusCode) {
    return "HTTP/1.1 "
           + LibraryWrapper::RFCWrapper::responseStatus(statusCode)
           + LibraryWrapper::RFCWrapper::contentType(fileType)
           + "Content-Length: "
           + std::to_string(contentLength)
           + "\n\n"
        ;
}

std::pair<std::string, std::string>
LibraryWrapper::RFCWrapper::parseRESTInformation(const std::string &requestContent) {
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
    return std::make_pair(method, Utils::CommonUtils::normalizeString(endPoint));
}
