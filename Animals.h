//
// Created by Czertilla on 18.12.2023.
//


#ifndef OASIS_ANIMALS_H
#define OASIS_ANIMALS_H

#include <string>
#include <vector>
#include "Vectors.h"
#include <set>
#include <ctime>
#include <string>
#include <map>
#include "timer.h"


class Animals {
private:
    double OLD_AGE = OLD_AGE_Animals;
    double REP_AGE = REP_AGE_Animals;
    constexpr const static float MIN_GEN = MIN_GEN_Animals;
    constexpr const static float MAX_GEN = MAX_GEN_Animals;
    static std::set<Animals*> population;
    std::map<std::string, float> effects;
    Vectors position;
    Vectors velocity;
    double lastUpdate;
    double age;
    double old;
    double rep;
    float mobility;
    float endurance;
    float stamina;
    float vigilance;
    float health;
    float satiety;
    float metabolism;
    bool femal;
    bool dead;
public:
    explicit Animals(const Vectors& pos);
    Animals(Animals* father, Animals* mother);

    static const std::set<Animals *> &getPopulation();

    Vectors getPosition();
    static float creategen(float fatherGen, float motherGen);
    [[nodiscard]] double getAge() const;
    [[nodiscard]] float getMobility() const;
    [[nodiscard]] float getEndurance() const;
    [[nodiscard]] float getOld() const;
    [[nodiscard]] float getRep() const;
    float getStamina();
    float getHealth();
    float getSatiety();
    void setVelocity(const Vectors &vect);
    [[nodiscard]] float getVigilance() const;
    [[nodiscard]] float getMetabolism() const;
    bool isFemal() const;


    void update();

    virtual void death();
};


#endif //OASIS_ANIMALS_H
