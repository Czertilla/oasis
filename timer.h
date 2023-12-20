//
// Created by Redmi on 19.12.2023.
//

#include <chrono>
#include "constants.h"

#ifndef OASIS_TIMER_H
#define OASIS_TIMER_H 1

namespace sc = std::chrono;

class timer {
private:
    static bool initialized;
    static double time;
    static long long realTime;
    static double timelineSpeed;
    static double mem;
public:
    timer();
    static long long getTime();
    static double getGap(long long a, long long b);
    static double getGap(double a, double b);
    static double get();
    static void setTimelineSpeed(double timelineSpeed);
    static void pause();

    static double getTimelineSpeed();

    static void resume();
};

#endif //OASIS_TIMER_H

