//
// Created by Redmi on 18.12.2023.
//

#include "Herbivores.h"
#include "Predators.h"

std::set<Predators*> Predators::population{};
std::set<Vectors*> Predators::coords{};

Predators::Predators(Predators* father, Predators* mother): Animals(father, mother) {
    saturation = SATURATION_Predators;
    Animals::HUNGER_SPEED = HUNGER_SPEED_Predators;
    coords.insert(&position);
    Animals::WALK_SPEED = WALK_SPEED_Predators;
    Predators::population.insert(this);
}

Predators::Predators(const Vectors  &position) : Animals(position) {
    Animals::HUNGER_SPEED = HUNGER_SPEED_Predators;
    coords.insert(&this->position);
    Animals::WALK_SPEED = WALK_SPEED_Predators;
    Predators::population.insert(this);
}

void Predators::death() {
    Predators::population.erase(this);
    Predators::coords.erase(&position);
    Animals::death();
}

void Predators::update() {
    Animals::update();
    auto pos = getPosition().getMultiplied(-1);
    if (this->getSatiety() < HUNGRY_LEVEL_Predators){
        for(auto herb : Herbivores::getPopulation()){
            auto distance = Vectors::getAmount(herb->getPosition(), pos);
            auto range = distance.length();
            if (range <= KILL_RANGE){
                herb->death();
                eat();
                std::cout << "Predators eats" << std::endl;
                break;
            }
            else if (range <= VIEW_DISTANCE_Predators * getVigilance()) {
                auto direction = distance.getDirection();
                direction.multiply(RUN_SPEED_Predators * getMobility());
                setVelocity(direction);
                return;
            }
        }
    }else if (getAge() >= getRep()){
        for(auto pred: Predators::population){
            if (pred == this or pred->getRep() < pred->getAge()) continue;
            auto distance = Vectors::getAmount(pred->getPosition(), pos);
            auto range = distance.length();
            if (range >= MATE_RANGE){
                pred->setSatiety(HUNGRY_LEVEL_Predators);
                this->setSatiety(HUNGRY_LEVEL_Predators);
                new Predators(this, pred);
                break;
            }
            else if (range <= VIEW_DISTANCE_Predators * getVigilance()){
                auto direction = distance.getDirection();
                direction.multiply((WALK_SPEED_Predators * getMobility()));
                setVelocity(direction);
                return;
            }
        }
    }
    brownianGo();
}


const std::set<Predators *> &Predators::getPopulation() {
    return Predators::population;
}

const std::set<Vectors *> &Predators::getCoords() {
    return coords;
}
