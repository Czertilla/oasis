#include <iostream>
#include "Herbivores.h"
#include <thread>
#include "timer.h"
#include <windows.h>
#include <winbgim.h>

void sleep(long long ms){
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

bool flagSim = true; // разрешение симулиовать
bool flagVis = true; // разрешить визуализировать

void updateGrass(){
    auto grass = *Herbivores::getGrass();
    auto herbs = *Herbivores::getPopulation();
    auto gap = herbs.size() - grass.size();
    if (gap <= 0) return;
    auto count = (int)(gap * GRASS_RECOVERY);
    for (int i=0; i < count; i++){
        Herbivores::addGrass();
    }
}

void simulate() {
    auto all = Animals::getPopulation();
    auto preds = Predators::getPopulation();
    auto herbs = Herbivores::getPopulation();
    while (not preds->empty() and not herbs->empty() and flagSim){
        for (Animals* indiv : *all){
            timer::pause();
            timer::resume(); // место остановки для дебага
            indiv->update();
        }
        updateGrass();
        sleep(100);
    }
    std::cout << preds->size() << " " << herbs->size() << " " << timer::get() << std::endl;
}

void visualize(){
    initwindow(X_BORDER_Screen*2, Y_BORDER_Screen * 2);
    while (flagVis){
        sleep(1);
        cleardevice();
        setcolor(RED);
        for (Predators* indiv: *Predators::getPopulation()){
            auto pos = indiv->getPosition();
            circle((int)pos.x + X_BORDER_Screen, (int)pos.y + Y_BORDER_Screen, DOT_SCREEN_RADIUS);
        }
        setcolor(BLUE);
        for (Herbivores* indiv: *Herbivores::getPopulation()){
            auto pos = indiv->getPosition();
            circle((int)pos.x + X_BORDER_Screen, (int)pos.y + Y_BORDER_Screen, DOT_SCREEN_RADIUS);
        }
        setcolor(GREEN);
        for(Vectors* coords: *Herbivores::getGrass()){
            auto pos = *coords;
            circle((int)coords->x + X_BORDER_Screen, (int)coords->y + Y_BORDER_Screen, DOT_SCREEN_RADIUS);
        }
    }
}

int main() {
    timer();
    timer::setTimelineSpeed(5);
    auto p = Predators(Vectors(0, 0));
    auto h = Herbivores(Vectors(100.0, 100.0));
    p.setVelocity(Vectors(4, 1));
    std::thread vis(visualize);
    std::thread sim(simulate);
    sleep(10);
    sim.join();
    std::cout << p.getStamina() << std::endl << p.getPosition().length();
    vis.join();
    return 0;
}
