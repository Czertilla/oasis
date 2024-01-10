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
    static const std::set<Vectors *> *getCoords();

protected:
    static std::set<Vectors*> coords;
public:
    explicit Predators(const Vectors& position); // наследованные кострукторы
    Predators(Predators* father, Predators* mother);
    // уникальный для класса геттер
    // наследованный метод обновления
    void update() override;

    static const std::set<Predators *> &getPopulation();

    // наследованный метод смерти
    void death() override;
};

#endif //OASIS_PREDATORS_H
