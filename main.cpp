#include <iostream>
#include "Predators.h"
#include <thread>
#include "timer.h"
#include "constants.h"


void sleep(long long ms){
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

int main() {
    auto a = Predators(Vectors(1, 2));
    auto now = getTime();
    sleep(5000);
    auto past = getTime();
    std::cout << getGap(now, past) << std::endl;
    timeLineSpeed = 100;
    sleep(5000);
    now = getTime();
    std::cout << getGap(past, now) << std::endl;
    return 0;
}
