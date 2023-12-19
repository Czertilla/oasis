//
// Created by Redmi on 19.12.2023.
//

#include "timer.h"

//
// Created by Redmi on 19.12.2023.
//

bool timer::initialized = false;
double timer::time = 0.0;
long long timer::realTime = 0;
double timer::timelineSpeed = 1.0;

long long timer::getTime() {
        auto t = sc::system_clock::now(); // get the current time

        auto since_epoch = t.time_since_epoch(); // get the duration since epoch

// I don't know what system_clock returns
// I think it's uint64_t nanoseconds since epoch
// Either way this duration_cast will do the right thing
        auto millis = sc::duration_cast<sc::milliseconds>(since_epoch);
        return millis.count();
}

double timer::getGap(long long a, long long b) {
    return (double) (b - a) / 1000 * timelineSpeed;
}

timer::timer() {
    if (not initialized) {
        initialized = true;
        timelineSpeed = 1.0;
        realTime = getTime();
        time = (double) realTime / 1000;
    }
}

void timer::setTimelineSpeed(double modifier) {
    if (modifier >= 0.0) {
        get();
        timer::timelineSpeed = modifier;
    }
}

double timer::get() {
    long long now = getTime();
    time += getGap(realTime, now);
    realTime = now;
    return time;
}

double timer::getGap(double a, double b) {
    return (b - a);
};



