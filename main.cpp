#include <iostream>
#include "Herbivores.h"
#include <thread>
#include "timer.h"

void sleep(long long ms){
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

int main() {
    timer();
    auto a = Predators(Vectors(1, 2));
    auto now = timer::get();
    sleep(5000);
    auto past = timer::get();
    std::cout << timer::getGap(now, past) << std::endl;
    timer::setTimelineSpeed(100);
    sleep(5000);
    auto second = timer::get();
    std::cout << timer::getGap(past, second) << std::endl << second;
    return 0;
}
