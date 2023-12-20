//
// Created by MacBook Pro on 20.12.2023.
//

#include "Herbivores.h"

std::set<Herbivores*> Herbivores::population{};

Herbivores::Herbivores(Animals* father, Animals* mother): Animals(father, mother) {
    Herbivores::population.insert(this);
}

Herbivores::Herbivores(const Vectors &position): Animals(position) {
    Herbivores::population.insert(this);
}

void Herbivores::death() {
    Animals::death();
    Herbivores::population.erase(this);
}

std::set<Herbivores *> &Herbivores::getPopulation() {
    return population;
}
