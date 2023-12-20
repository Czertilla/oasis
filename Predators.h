//
// Created by Redmi on 18.12.2023.
//

#ifndef OASIS_PREDATORS_H
#define OASIS_PREDATORS_H

#include "Animals.h"

// класс Хищники, наследуется от базового класса Животные
class Predators: public Animals {
private:
    static std::set<Predators*> population; // популяция только хищников
public:
    explicit Predators(const Vectors& position); // наследованные кострукторы
    Predators(Animals* father, Animals* mother);
    // уникальный для класса геттер
    static std::set<Predators *> &getPopulation();

    // наследованный метод обновления
    void update() override;

    // наследованный метод смерти
    void death() override;
};

#endif //OASIS_PREDATORS_H
