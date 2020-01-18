//
// Created by kuribohkute on 17/01/2020.
//

#ifndef DTLMINIPROJECT_OTHERUTILS_H
#define DTLMINIPROJECT_OTHERUTILS_H

#include <sstream>
#include <cstring>
#include <iostream>
#include <sys/stat.h>

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

#endif //DTLMINIPROJECT_OTHERUTILS_H
