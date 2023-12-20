//
// Created by MacBook Pro on 20.12.2023.
//

#ifndef OASIS_HERBIVORES_H
#define OASIS_HERBIVORES_H
#include "Predators.h"

// класс Травоядные, наследуется от базового класса Животные
class Herbivores: public Animals {
private:
    static std::set<Herbivores*> population; // популяция только травоядных
public:
    explicit Herbivores(const Vectors& position); // наследованные кострукторы
    Herbivores(Animals* father, Animals* mother);
    // уникальный для класса геттер
    static std::set<Herbivores *> &getPopulation();

    // наследованный метод смерти
    void death() override;
};


#endif //OASIS_HERBIVORES_H