//
// Created by kuribohkute on 10/02/2021.
//

#ifndef SIMPLECPPSERVER_FILEUTILS_H
#define SIMPLECPPSERVER_FILEUTILS_H

#include <string>

namespace Utils {
    class FileUtils {
    public:
        static void transferFile(const int &socketFileDescriptor, const std::string &filePath);
    };
}

#endif //SIMPLECPPSERVER_FILEUTILS_H
