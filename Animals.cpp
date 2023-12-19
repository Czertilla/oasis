//
// Created by Redmi on 18.12.2023.
//

#include "Animals.h"
#include "Randomizer.h"
#include <vector>

std::set<Animals*> Animals::population{};

Animals::Animals(const Vectors& pos) {
    lastUpdate = getTime();
    population.insert(this);
    position = pos;
    age = 0.0;
    old = OLD_AGE;
    rep = REP_AGE;
    mobility = 1.0;
    endurance = 1.0;
    stamina = 100.0;
    health = 100.0;
    satiety = 100.0;
    metabolism = 1.0;
    femal = true;
}

Animals::Animals(Animals* father, Animals* mother) {
    lastUpdate = getTime();
    population.insert(this);
    position = mother->getPosition();
    age = 0.0;
    mobility = creategen(father->getMobility(), mother->getMobility());
    old = creategen(father->getOld(), mother->getOld());
    rep = creategen(father->getRep(), mother->getRep());
    endurance = creategen(father->getEndurance(), mother->getEndurance());
    stamina = 100.0;
    health = 100.0;
    satiety = 100.0;
    metabolism = creategen(father->getMetabolism(), mother->getMetabolism());
    femal = endurance > mobility;
}


float Animals::creategen(float fatherGen, float motherGen){
    return (fatherGen + motherGen) / 2 * (float) randDouble(MIN_GEN, MAX_GEN);
}

Vectors Animals::getPosition()  {
    return position;
}

float Animals::getAge() const  {
    return age;
}

float Animals::getMobility() const  {
    return mobility;
}

float Animals::getEndurance() const{
    return endurance;
}

float Animals::getStamina(){
    return stamina;
}

float Animals::getHealth(){
    return health;
}

float Animals::getSatiety(){
    return satiety;
}

float Animals::getMetabolism() const{
    return metabolism;
}

bool Animals::isFemal() {
    return femal;
}

void Animals::update(){
    long long timeUpdate = getTime();
    health += (float) effects.count("healing")  * (old - age) / age ;
    if (health < 100.0 and effects.count("healing") == 0){
        effects["healing"] = -1;
        metabolism += 0.5;
    }
}

void Animals::death(){
    health = 0.0;
    population.erase(this);
}

float Animals::getOld() const {
    return old;
}

float Animals::getRep() const {
    return rep;
}

