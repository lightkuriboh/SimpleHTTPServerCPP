
#ifndef SIMPLECPPSERVER_COMMONUTILS_H
#define SIMPLECPPSERVER_COMMONUTILS_H

#include <string>

namespace Utils {
    class CommonUtils {
    private:
        static void decode(const std::string &s, std::string &destination) {
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
    public:
        static std::string normalizeString(const std::string &input) {
            std::string ans;
            Utils::CommonUtils::decode(input, ans);
            return ans;
        }
    };
}

#endif //SIMPLECPPSERVER_COMMONUTILS_H
