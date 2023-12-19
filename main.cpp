#include <iostream>
#include "Herbivores.h"
#include <thread>
#include "timer.h"

void sleep(long long ms){
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

int main() {
    timer();
    auto p = Predators(Vectors(0, 0));
    Vectors vel = Vectors(1, 1);
    for (int i=0; i<4; i++){
        vel.add(Vectors(1, 0));
        p.setVelocity(vel);
        timer::setTimelineSpeed(0.0);
        p.update();
        timer::setTimelineSpeed(1.0);
        sleep(1000);
    }
    std::cout << p.getStamina() << std::endl << p.getPosition().length();
    return 0;
}
