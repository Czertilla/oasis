//
// Created by MacBook Pro on 20.12.2023.
//

#ifndef OASIS_HERBIVORES_H
#define OASIS_HERBIVORES_H
#include "Predators.h"

class Herbivores {
    private:
        static std::set<Herbivores*> population;
    public:
        explicit Herbivores(const Vectors& position);
        Herbivores(Animals* father, Animals* mother);

        void death() override;
};


#endif //OASIS_HERBIVORES_H
