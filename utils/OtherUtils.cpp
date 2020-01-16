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
