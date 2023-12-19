//
// Created by MacBook Pro on 20.12.2023.
//

#include "Herbivores.h"

std::set<Herbivores*> Herbivores::population{};

Herbivores::Herbivores(Animals* father, Animals* mother): Animals(father, mother) {
    population.insert(this);
}

Herbivores::Herbivores(const Vectors &position): Animals(position) {
    population.insert(this);
}

void Herbivores::death() {
    Animals::death();
    population.erase(this);
}

