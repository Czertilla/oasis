#include <iostream>
#include "Herbivores.h"
#include <thread>
#include "timer.h"
#include <winbgim.h>
#include "Randomizer.h"
#include "visualise.h"
#include "future"

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

void sleep(long long ms){
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

bool flagSim = true; // разрешение симулиовать
bool flagVis = true; // разрешить визуализировать

void draw(const std::set<Vectors*>& data){
    for(Vectors* i: data)
        circle((int)i->x + X_BORDER_Screen, (int)i->y + Y_BORDER_Screen, DOT_SCREEN_RADIUS);
}

char* getText(long long* lastUpdate){
    std::string text;
    text += std::to_string(Predators::getCoords().size()) + ":";
    text += std::to_string(Herbivores::getCoords().size());
    auto date = (long) timer::get();
    text+= "    " + std::to_string((int)(timer::get()/HOUR)) + ":";
    date %= HOUR;
    text+= std::to_string((int)(date/MINUTE)) + ':';
    date %= MINUTE;
    text+=std::to_string((date));
    auto now = timer::getTime();
    text+= "    " + std::to_string(1000. / (double)(now - *lastUpdate));
    *lastUpdate = now;
    return const_cast<char*>(text.c_str());
}

bool swap(bool page){
    setactivepage(page);
    page = !page;
    setvisualpage(page);
    return page;
}

void calculate(const std::set<Vectors*>& coords, int* res){
    res[0] = coords.size();
    int i = 1;
    for(auto pos:coords){
        res[i] = (int)pos->x + X_BORDER_Screen;
        res[i+1] = (int)pos->y + Y_BORDER_Screen;
        i+= 2;
    }
}

void visualize(){
    auto herbivores = Herbivores::getCoords();
    auto predators = Predators::getCoords();
    auto grass = Herbivores::getGrass();
    initwindow(X_BORDER_Screen*2, Y_BORDER_Screen * 2 + TEXT_HEIGHT * STRINGS_COUNT, "Oasis");
    bool page;
    long long lastUpdate = timer::getTime();
    while (flagVis){
        page = swap(page);
        cleardevice();
        setcolor(RED);
        for (Predators* indiv: Predators::getPopulation()){
            auto pos = indiv->getPosition();
            circle((int)pos.x + X_BORDER_Screen, (int)pos.y + Y_BORDER_Screen, DOT_SCREEN_RADIUS);
        }
        setcolor(BLUE);
        for (Herbivores* indiv: Herbivores::getPopulation()){
            auto pos = indiv->getPosition();
            circle((int)pos.x + X_BORDER_Screen, (int)pos.y + Y_BORDER_Screen, DOT_SCREEN_RADIUS);
        }
        setcolor(GREEN);
        for(Vectors* coords: Herbivores::getGrass()){
            auto pos = *coords;
            circle((int)coords->x + X_BORDER_Screen, (int)coords->y + Y_BORDER_Screen, DOT_SCREEN_RADIUS);
        }
    }
}


void updateGrass(){
    auto grass = Herbivores::getGrass();
    auto herbs = Herbivores::getPopulation();
    auto gap = herbs.size() - grass.size();
    if (gap <= 0) return;
    auto count = (int)(gap * GRASS_RECOVERY);
    for (int i=0; i < count; i++){
        Herbivores::addGrass();
    }
}

void simulate() {
    while (not Predators::getPopulation().empty() and not Herbivores::getPopulation().empty() and flagSim){
        auto population = Animals::getPopulation();
        for (Animals* indiv : population){
            if (indiv->isDead()) continue;
            timer::pause();
            timer::resume();// место остановки для дебага
            indiv->update();
        }
        Herbivores::updateGrass();
        sleep(1);
    }
    timer::setTimelineSpeed(0);
    std::cout << Predators::getPopulation().size() << " "
    << Herbivores::getPopulation().size() << " " << timer::get() << std::endl;
}


int main() {
    flagSim = true;
    flagVis = true;
    timer();
    timer::setTimelineSpeed(timeLineSpeed);
    for (int i=0; i<START_COUNT_Predators; i++){
        new Predators(Vectors(randDouble(-X_BORDER_World, +X_BORDER_World),
                          randDouble(-Y_BORDER_World, +Y_BORDER_World)));
    }
    for (int i=0; i<START_COUNT_Herbivores; i++){
        new Herbivores(Vectors(randDouble(-X_BORDER_World, +X_BORDER_World),
                          randDouble(-Y_BORDER_World, +Y_BORDER_World)));
    }
    for (int i=0; i<START_COUNT_Grass; i++){
        Herbivores::addGrass(new Vectors(randDouble(-X_BORDER_World, +X_BORDER_World),
                          randDouble(-Y_BORDER_World, +Y_BORDER_World)));
    }
//    auto p = Predators(Vectors(-200, -200));
//    auto p2 = Predators(Vectors(-200, -210));
//    auto h = Herbivores(Vectors(100.0, 100.0));
    Herbivores::addGrass(new Vectors(200.0, 200.0));
//    p.setVelocity(Vectors(4, 1));
    std::thread vis(visualize);
    std::thread sim(simulate);
    sleep(10);
    sim.join();
    vis.join();
    return 0;
}
