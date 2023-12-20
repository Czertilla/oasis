#include <iostream>
#include "Herbivores.h"
#include <thread>
#include "timer.h"

void sleep(long long ms){
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

bool flag = true; // разрешение симулиовать

void simulate() {
    auto all = Animals::getPopulation();
    auto preds = Predators::getPopulation();
    auto herbs = Herbivores::getPopulation();
    while (not preds.empty() and not herbs.empty() and flag){
        for (Animals* indiv : all){
            timer::pause();
            timer::resume(); // место остановки для дебага
            indiv->update();
        }
        sleep(100);
    }
    std::cout << preds.size() << " " << herbs.size() << " " << timer::get();
}

int main() {
    timer();
    auto p = Predators(Vectors(0, 0));
    auto h = Herbivores(Vectors(19.0, 0));
    std::thread sim(simulate);
    sleep(10);
    sim.join();
    std::cout << p.getStamina() << std::endl << p.getPosition().length();
    return 0;
}
