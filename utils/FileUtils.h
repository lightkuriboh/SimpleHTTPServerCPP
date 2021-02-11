
#ifndef SIMPLECPPSERVER_FILEUTILS_H
#define SIMPLECPPSERVER_FILEUTILS_H

#include <sys/stat.h>

#include <string>

namespace Utils {
    class FileUtils {
    public:
        static bool isFilePath(const std::string& str) {
            auto n = (int)str.size();
            for (auto i = n - 1; i >= 0; --i) {
                if (str[i] == '.' && i != n - 1) {
                    return true;
                }
            }
            return false;
        }

        static int getFileSize(const std::string &filePath) {
            struct stat st{};
            bool exist = stat(filePath.c_str(), &st) == 0;
            if (!exist) {
                return -1;
            }
            return st.st_size;
        }

        static std::string getFileType(const std::string &fileName) {
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
    };
}

#endif //SIMPLECPPSERVER_FILEUTILS_H
