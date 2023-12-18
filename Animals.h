//
// Created by Czertilla on 18.12.2023.
//


#ifndef OASIS_ANIMALS_H
#define OASIS_ANIMALS_H


//#include <windows.h>
#include <string>
#include <vector>
#include "Vectors.h"
#include <set>
#include <ctime>
#include <string>
#include <map>

class Animals {
private:
    float OLD_AGE = 20;
    float REP_AGE = 1;
public:
    float getOld() const;

    float getRep() const;

private:
    constexpr static float MIN_GEN = 0.8;
    constexpr static float MAX_GEN = 2.7;
    std::set<Animals*> population;
    std::map<std::string, float> effects;
    Vectors position;
    Vectors velocity;
    double lastUpdate;
    float age;
    float old;
    float rep;
    float mobility;
    float endurance;
    float stamina;
    float health;
    float satiety;
    float metabolism;
    bool femal;
public:
    explicit Animals(const Vectors& pos);
    Animals(Animals* father, Animals* mother);

    Vectors getPosition();
    static float creategen(float fatherGen, float motherGen);
    [[nodiscard]] float getAge() const;
    [[nodiscard]] float getMobility() const;
    [[nodiscard]] float getEndurance() const;
    float getStamina();
    float getHealth();
    float getSatiety();
    [[nodiscard]] float getMetabolism() const;
    bool isFemal();

    void update();

    virtual void death();
};


#endif //OASIS_ANIMALS_H
