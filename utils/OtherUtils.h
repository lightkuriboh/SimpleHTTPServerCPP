//
// Created by kuribohkute on 17/01/2020.
//

#ifndef DTLMINIPROJECT_OTHERUTILS_H
#define DTLMINIPROJECT_OTHERUTILS_H

#include <iostream>
#include <sstream>
#include <chrono>

namespace Utils {
    class OtherUtils {
    public:
        static std::string intToString(int x);
        static long getTimeNow();
    };
}

#endif //DTLMINIPROJECT_OTHERUTILS_H
