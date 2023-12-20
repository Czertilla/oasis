//
// Created by Redmi on 18.12.2023.
//

#include "Herbivores.h"
#include "Predators.h"

std::set<Predators*> Predators::population{};

Predators::Predators(Animals* father, Animals* mother): Animals(father, mother) {
    Predators::population.insert(this);
}

Predators::Predators(const Vectors  &position) : Animals(position) {
    Predators::population.insert(this);
}

void Predators::death() {
    Animals::death();
    Predators::population.erase(this);
}

void Predators::update() {
    Animals::update();
    auto pos = getPosition().getMultiplied(-1);
    if (this->getSatiety() < HUNGRY_LEVEL_Predators){
        for(Herbivores* herb : Herbivores::getPopulation()){
            auto distance = Vectors::getAmount(herb->getPosition(), pos);
            auto range = distance.length();
            if (range <= KILL_RANGE){
                herb->death();
                eat();
                break;
            }
            else if (range <= VIEW_DISTANCE_Predators * getVigilance()) {
                auto direction = distance.getDirection();
                direction.multiply(RUN_SPEED_Predators * getMobility());
                setVelocity(direction);
                break;
            }
        }
    }else{

    }
}

std::set<Predators *>& Predators::getPopulation() {
    return population;
}


