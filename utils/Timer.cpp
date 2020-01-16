//
// Created by kuribohkute on 16/01/2020.
//

#include "Timer.h"

long Utils::Timer::getTimeNow() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch()).count();
}

