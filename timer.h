//
// Created by Redmi on 19.12.2023.
//

#include <chrono>
#include "constants.h"

#ifndef OASIS_TIMER_H
#define OASIS_TIMER_H 1
namespace sc = std::chrono;


static long long getTime() {
    auto time = sc::system_clock::now(); // get the current time

    auto since_epoch = time.time_since_epoch(); // get the duration since epoch

// I don't know what system_clock returns
// I think it's uint64_t nanoseconds since epoch
// Either way this duration_cast will do the right thing
    auto millis = sc::duration_cast<sc::milliseconds>(since_epoch);
    return millis.count();
};

static double getGap(long long a, long long b){
    return (double) (b - a) / 1000 * timeLineSpeed;
}
#endif //OASIS_TIMER_H

