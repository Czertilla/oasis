//
// Created by Redmi on 18.12.2023.
//

#include "Predators.h"

std::set<Predators*> Predators::population{};

Predators::Predators(Animals* father, Animals* mother): Animals(father, mother) {
    population.insert(this);
}

Predators::Predators(const Vectors  &position) : Animals(position) {
    population.insert(this);
}

void Predators::death() {
    Animals::death();
    population.erase(this);
}

void Predators::update() {
    Animals::update();
    if (this->getSatiety() < HUNGRY_LEVEL_Predators){
//        find
    }else{

    }
}


