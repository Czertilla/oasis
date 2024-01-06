//
// Created by MacBook Pro on 20.12.2023.
//

#include "Herbivores.h"
#include "Randomizer.h"

std::set<Herbivores*> Herbivores::population{};
std::set<Vectors*> Herbivores::grass{};
std::set<Vectors*> Herbivores::coords{};
double Herbivores::lastUpdate = 0.0;

Herbivores::Herbivores(Animals* father, Animals* mother): Animals(father, mother) {
    Animals::HUNGER_SPEED = HUNGER_SPEED_Herbivores;
    coords.insert(&position);
    Animals::WALK_SPEED = WALK_SPEED_Herbivores;
    Herbivores::population.insert(this);
}

Herbivores::Herbivores(const Vectors &position): Animals(position) {
    Animals::HUNGER_SPEED = HUNGER_SPEED_Herbivores;
    coords.insert(&this->position);
    Animals::WALK_SPEED = WALK_SPEED_Herbivores;
    Herbivores::population.insert(this);
}

const std::set<Vectors *> &Herbivores::getCoords() {
    return coords;
}

void Herbivores::death() {
    Herbivores::population.erase(this);
    Herbivores::coords.erase(&position);
    Animals::death();
}


const std::set<Vectors *> &Herbivores::getGrass() {
    return grass;
}

void Herbivores::addGrass() {
    grass.insert(new Vectors(randDouble(-340.0, 340.0), randDouble(-340.0, 340.0)));
}


const std::set<Herbivores *> &Herbivores::getPopulation() {
    return Herbivores::population;
}

void Herbivores::update() {
    Animals::update();
    auto pos = getPosition().getMultiplied(-1);
    for (auto pred : Predators::getCoords()){
        auto distance = Vectors::getAmount(*pred, pos);
        auto range = distance.length();
        if (range <= VIEW_DISTANCE_Herbivores * getVigilance()){
            auto direction = distance.getDirection();
            direction.multiply(-1 * RUN_SPEED_Herbivores * getMobility());
            setVelocity(direction);
            return;
        }
    }
    if (getAge() >= getRep()){
        for(auto herb: Herbivores::population){
            if (herb == this or herb->getRep() < herb->getAge()) continue;
            auto distance = Vectors::getAmount(herb->getPosition(), pos);
            auto range = distance.length();
            if (range >= MATE_RANGE){
                herb->setSatiety(herb->getSatiety() - 10);
                this->setSatiety(getSatiety() - 10);
//                std::cout << "Herbivores mate\n";
                new Herbivores(this, herb);
                break;
            }
            else if (range <= VIEW_DISTANCE_Herbivores * getVigilance()){
                auto direction = distance.getDirection();
                direction.multiply((WALK_SPEED_Herbivores * getMobility()));
                setVelocity(direction);
                return;
            }
        }
    }
    if (this->getSatiety() < HUNGRY_LEVEL_Herbivores){
        for(auto grass : Herbivores::getGrass()){
            auto distance = Vectors::getAmount(*grass, pos);
            auto range = distance.length();
            if (range <= KILL_RANGE){
                eraseGrass(grass);
                eat();
//                std::cout << "Herbivores eats" << std::endl;
                break;
            }
            else if (range <= VIEW_DISTANCE_Herbivores * getVigilance()){
                auto direction = distance.getDirection();
                direction.multiply(WALK_SPEED_Herbivores * getMobility());
                setVelocity(direction);
                return;
            }
        }
    }
    brownianGo();
}

void Herbivores::eraseGrass(Vectors* gr) {
    Herbivores::grass.erase(gr);
}

void Herbivores::addGrass(Vectors* pos) {
    Herbivores::grass.insert(pos);
}

void Herbivores::updateGrass() {
    auto currTime = timer::get();
    if (currTime - lastUpdate >= GRASS_FREQUENCY){
        lastUpdate = currTime;
        auto count = grass.size();
        for (int i=0; i < (int)(START_COUNT_Grass * GRASS_RECOVERY/(float)count
        * population.size()/START_COUNT_Herbivores); i++) {
            Herbivores::addGrass();
        }
        Herbivores::addGrass();
    }
}
