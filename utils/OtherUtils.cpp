//
// Created by kuribohkute on 17/01/2020.
//

#include "OtherUtils.h"

std::string Utils::OtherUtils::intToString(int x) {
    std::string res;
    std::stringstream ss;
    ss << x;
    ss >> res;
    return res;
}

long Utils::OtherUtils::getTimeNow() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch()).count();
}
