//
// Created by Redmi on 18.12.2023.
//

#include "Predators.h"

Predators::Predators(Animals* father, Animals* mother): Animals(father, mother) {
    population.insert(this);
}

Predators::Predators(const Vectors& position) : Animals(position) {
    population.insert(this);
}

void Predators::death() {
    Animals::death();
    population.erase(this);
}


