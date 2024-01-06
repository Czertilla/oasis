//
// Created by Redmi on 18.12.2023.
//

#include "Animals.h"
#include "Randomizer.h"
#include <vector>

std::set<Animals*> Animals::population{};

Animals::Animals(const Vectors& pos) {
    lastUpdate = timer::get();
    population.insert(this);
    position = pos;
    age = 0.0;
    old = OLD_AGE_Animals;
    rep = REP_AGE_Animals;
    vigilance = 1.0;
    mobility = 1.0;
    endurance = 1.0;
    stamina = 100.0;
    health = 100.0;
    satiety = 100.0;
    metabolism = 1.0;
    saturation = SATURATION_Animals;
    femal = true;
    dead = false;
}

Animals::Animals(Animals* father, Animals* mother) {
    lastUpdate = timer::get();
    population.insert(this);
    position = mother->getPosition();
    age = 0.0;
    mobility = creategen(father->getMobility(), mother->getMobility());
    old = creategen(father->getOld(), mother->getOld());
    rep = creategen(father->getRep(), mother->getRep());
    endurance = creategen(father->getEndurance(), mother->getEndurance());
    vigilance = creategen(father->getVigilance(), mother->getVigilance());
    stamina = 100.0;
    health = 100.0;
    satiety = 100.0;
    metabolism = creategen(father->getMetabolism(), mother->getMetabolism());
    saturation = SATURATION_Animals;
    femal = endurance > mobility;
    dead = false;
}


float Animals::creategen(float fatherGen, float motherGen){
    return (fatherGen + motherGen) / 2 * (float) randDouble(MIN_GEN, MAX_GEN);
}

Vectors Animals::getPosition()  {
    return position;
}

double Animals::getAge() const  {
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

bool Animals::isFemal() const {
    return femal;
}

void Animals::update(){
    double currUpdate = timer::get();
    double timeGap = timer::getGap(lastUpdate, currUpdate);
    age += timeGap;
    if(age >= OLD_AGE_Animals * old){
        this->death();
        return;
    }
    auto gapVect = velocity.getMultiplied(timeGap);
    position.add(gapVect);
    stamina -= STAMINA_LOST_SPEED * (float) (gapVect.length() * velocity.length()) / endurance;
    if (health < MIN_HEALTH_LEVEL){
        this->death();
        return;
    }
    bool hmflag{false}, smflag{false};
    if (health < MAX_HEALTH_LEVEL) {
        hmflag = true;
        metabolism += MB_HEALING_COST;
        health += metabolism * (float) timeGap;
    }
    if (stamina < MIN_STAMINA_LEVEL) velocity = Vectors(0, 0);
//    health += effects.count("healing")  * (old - age) / age ;
//    if (health < 100.0 and effects.count("healing") == 0){
//        effects["healing"] = -1;
//        metabolism += 0.5;
//    }
    if (stamina < MAX_STAMINA_LEVEL){
        smflag = true;
        metabolism += MB_RECUPERATION_COST;
        stamina += metabolism * (float) timeGap;
    }
    satiety -= (float)this->HUNGER_SPEED * metabolism * (float)timeGap;
    if(satiety <= 0.0){
        this->death();
        return;
    }
    if(hmflag) metabolism -= MB_HEALING_COST;
    if(smflag) metabolism -= MB_RECUPERATION_COST;
    if(position.x > X_BORDER_World) position.x = X_BORDER_World;
    if(position.x < -X_BORDER_World) position.x = - X_BORDER_World;
    if(position.y > Y_BORDER_World) position.y = Y_BORDER_World;
    if(position.y < -Y_BORDER_World) position.y = - Y_BORDER_World;
    lastUpdate = currUpdate;
}

void Animals::death(){
    health = 0.0;
    population.erase(this);
    dead = true;
}

float Animals::getOld() const {
    return old * OLD_AGE_Animals;
}

float Animals::getRep() const {
    return rep * REP_AGE_Animals;
}

float Animals::getVigilance() const {
    return vigilance;
}

void Animals::setVelocity(const Vectors &vect) {
    Animals::velocity = vect;
}


void Animals::eat() {
    satiety += saturation;
    if (satiety > 100.0) satiety = 100.0;
}

const std::set<Animals *> &Animals::getPopulation() {
    return population;
}

bool Animals::isDead() const {
    return dead;
}

void Animals::brownianGo() {
    if (velocity.length() == 0){
        velocity = Vectors(randDouble(-1, 1), randDouble(-1, 1)).getDirection();
    }
    else {
        auto x{velocity.x}, y{velocity.y};
        float RB = 0.4;
        velocity.x += randDouble(-RB * x, RB * x);
        velocity.y += randDouble(-RB * y, RB * y);
        velocity = velocity.getDirection();
    }
    velocity.multiply(WALK_SPEED * mobility);
}

void Animals::setSatiety(float sat) {
    Animals::satiety = sat;
}

const Vectors &Animals::getVelocity() const {
    return velocity;
}

