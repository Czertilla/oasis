//
// Created by Redmi on 18.12.2023.
//

#include "Randomizer.h"
#include <random>

double randDouble(double a, double b) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(a, b);
    return dist(mt);
};
