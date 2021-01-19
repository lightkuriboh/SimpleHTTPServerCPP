
#ifndef SIMPLECPPSERVER_OTHERUTILS_H
#define SIMPLECPPSERVER_OTHERUTILS_H

#include <string>

namespace Utils {
    class OtherUtils {
    private:
        static void decode(const std::string &s, std::string &destination);
    public:
        static std::string intToString(int x);
        static std::string normalizeString(const std::string &input);
        static std::string getFileType(const std::string &fileName);
        static int getFileSize(const std::string &filePath);
    };
}

#endif //SIMPLECPPSERVER_OTHERUTILS_H
