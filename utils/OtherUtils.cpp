
#include "OtherUtils.h"

#include <sys/stat.h>

#include <sstream>

std::string Utils::OtherUtils::intToString(int x) {
    std::string res;
    std::stringstream ss;
    ss << x;
    ss >> res;
    return res;
}

std::string Utils::OtherUtils::normalizeString(const std::string &input) {
    std::string ans;
    Utils::OtherUtils::decode(input, ans);
    return ans;
}

void Utils::OtherUtils::decode(const std::string &s, std::string &destination) {
    auto isAlphabetical = [] (char x) {
        return	(x >= '0' && x <= '9')	||
                  (x >= 'a' && x <= 'f')	||
                  (x >= 'A' && x <= 'F');
    };
    const auto n = s.size();
    for (auto i = 0; i < n; i++) {
        auto c = s[i];
        if (c == '+') {
            c = ' ';
        } else {
            if (c == '%' && i <= n - 3
                             && isAlphabetical(s[i + 1])
                             && isAlphabetical(s[i + 2])
                    ) {
                auto a = s[i + 1];
                auto b = s[i + 2];

                if (a >= 'a') {
                    a -= 'a' - 'A';
                }
                if (a >= 'A') {
                    a -= ('A' - 10);
                } else {
                    a -= '0';
                }
                if (b >= 'a') {
                    b -= 'a' - 'A';
                }
                if (b >= 'A') {
                    b -= ('A' - 10);
                } else {
                    b -= '0';
                }
                c = 16 * a + b;
                i += 2;
            }
        }
        destination += c;
    }
}

std::string Utils::OtherUtils::getFileType(const std::string &fileName) {
    auto n = fileName.size();
    std::string ans;
    bool foundDot = false;
    for (auto i = 0; i < n; i++) {
        if (foundDot) {
            ans += fileName[i];
        }
        if (fileName[i] =='.') {
            foundDot = true;
        }
    }
    return ans;
}

int Utils::OtherUtils::getFileSize(const std::string &filePath) {
    struct stat st{};
    bool exist = stat(filePath.c_str(), &st) == 0;
    if (!exist) {
        return -1;
    }
    return st.st_size;
}
