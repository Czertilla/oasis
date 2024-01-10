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
#include <iostream>


// Базовый класс Животные, для наследования другим подвидам. Описывает общие для всех
// животных механики поведения и жизнедеятиельности
class Animals {
private:
    constexpr const static float MIN_GEN = MIN_GEN_Animals; // минимальный случайный множител гена
    constexpr const static float MAX_GEN = MAX_GEN_Animals; // максимальный случайный множитель гена
    static std::set<Animals*> population; // популяция всех животных
    Vectors velocity; // скорость (изменение позиции в секунду)
    double lastUpdate; // время в секундах в мире моделирования, когда последний раз обновлялась инфа об особи
    double age; // возраст в секундах
    double old; //ген старого возраста (множитель общего для класса значения)
    double rep; //ген репродуктивного возраста (тожемножитель)
    float mobility; //ген мобильности
    float endurance; //ген выносливости
    float stamina; //шкала выносливости
    float vigilance;// ген дальности зрения
    float health;// шкала здоровья
    float satiety;// шкала сытости
    float metabolism;// ген метаболизма
    bool femal;// является ли особь самкой
    bool dead;// мертва ли особь
protected:
    double saturation;
//    std::map<std::string, float> effects;
    Vectors position; // позиция
public:
    void setSatiety(float satiety);

public:
    double HUNGER_SPEED = HUNGER_SPEED_Animals;
    double WALK_SPEED   = WALK_SPEED_Animals;
    explicit Animals(const Vectors& pos); // конструктор для искуственного рождения (выставление на координаты)
//    стандартной особи)
    Animals(Animals* father, Animals* mother); // конструктор для естественного рождения (с механикой генетики)

    static float creategen(float fatherGen, float motherGen);
    void brownianGo();

//    далее идет ряд геттеров для приватных полей класса и объекта
    Vectors getPosition();

    bool isDead() const;

    static const std::set<Animals *> &getPopulation();

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

//  обновление информации об особи, происходит каждую итерацию по популяции
    virtual void update();

    const Vectors &getVelocity() const;

    void eat();

//    вызывается при смерти особи
    virtual void death();
};


#endif //OASIS_ANIMALS_H
