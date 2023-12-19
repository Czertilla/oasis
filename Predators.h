//
// Created by Redmi on 18.12.2023.
//

#ifndef OASIS_PREDATORS_H
#define OASIS_PREDATORS_H

#include "Animals.h"

class Predators: public Animals {
private:
    static std::set<Predators*> population;
public:
    explicit Predators(const Vectors& position);
    Predators(Animals* father, Animals* mother);

    void death() override;
};

#endif //OASIS_PREDATORS_H
