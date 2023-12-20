//
// Created by MacBook Pro on 20.12.2023.
//

#include "Herbivores.h"
#include "Randomizer.h"

std::set<Herbivores*> Herbivores::population{};
std::set<Vectors*> Herbivores::grass{};

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

std::set<Herbivores *>* Herbivores::getPopulation() {
    return &population;
}

const std::set<Vectors *>* Herbivores::getGrass() {
    return &grass;
}

void Herbivores::addGrass() {
    grass.insert(new Vectors(randDouble(-340.0, 340.0), randDouble(-340.0, 340.0)));
}
