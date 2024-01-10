//
// Created by Redmi on 18.12.2023.
//

#include "Herbivores.h" // заголовочный файл травоядных, в него включён файл класса Животные для наследования
#include "Predators.h" // заголовочный файл хищники
// это исходный файл класса Хищников, здесь описаны уникальные для хищников особенности, наследуется от класса
// Животные (см. файл Animals.cpp)
std::set<Predators*> Predators::population{};// популяция хищников, множество всех хищников (без травоядных)
std::set<Vectors*> Predators::coords{};// множество указателей координат всех особей, для отображения на экран

Predators::Predators(Predators* father, Predators* mother): Animals(father, mother) {
//    конструктор класса Хищники для случая, когда особь выставляется вручную на координаты, наследует соответсвующий
//    конструктор класса Животные
    saturation = SATURATION_Predators;; // выставляется уникальный для этого класса множитель голода
    Animals::HUNGER_SPEED = HUNGER_SPEED_Predators;// выставляется уникальный
    coords.insert(&position); // множество координат класса пополняется указателем на вектор позиции особи
    Animals::WALK_SPEED = WALK_SPEED_Predators;// выставляется уникальный для этого класса множитель скорости ходьбы
    Predators::population.insert(this);// популяция хищников пополняется указателем на особь
    setSatiety(HUNGRY_LEVEL_Predators);// выставляется уникальный для особей начальный уровень сытости
}

Predators::Predators(const Vectors  &position) : Animals(position) {
//    тот же конструктор, но дл я случая когда новая особь поялвяется в результате спаривания двух других особей.
    Animals::HUNGER_SPEED = HUNGER_SPEED_Predators;
    coords.insert(&this->position);
    Animals::WALK_SPEED = WALK_SPEED_Predators;
    Predators::population.insert(this);
    setSatiety(HUNGRY_LEVEL_Predators);
}

void Predators::death() {
    // метод вызываемый в случае гибели особи
    Predators::population.erase(this); // исключение особи из популяции Хищников
    Predators::coords.erase(&position); // прекращение отображения координат особи на экране
    Animals::death(); // вызов родительского метода
}

void Predators::update() {
    // метод описывает поведенческие особенности особи, вызывается раз в тик для обновления состояния, положения и тд.
    Animals::update(); // вызов родительского метода обновления особи
    auto pos = getPosition().getMultiplied(-1); // обратный вектор для удобного нахождения расстояний
    if (this->getSatiety() < HUNGRY_LEVEL_Predators){ // в начале проверяется, не голодная ли особь
        for(auto herb : Herbivores::getPopulation()){ // итерация по популяции травоядных
            auto distance = Vectors::getAmount(herb->getPosition(), pos); // вычисление дистанции
            auto range = distance.length(); // расстояния
            if (range <= KILL_RANGE){ // если цель достаточно близко, чтобы ее съесть
                herb->death(); // цель погибает
                eat(); // особь питается целью
                return; // в этом тике действия прекращаются
            } // если же цель слишком далеко для этого, но достаточно близко чтобы ее заметить
            else if (range <= VIEW_DISTANCE_Predators * getVigilance()) {
                auto direction = distance.getDirection(); // берется направление на цель
                direction.multiply(RUN_SPEED_Predators * getMobility()); // умножается с учетом мобильности
                setVelocity(direction); // устанавливается как вектор скорости особи, теперь она бежит к цели
                return; // обновление на этом завершается
            }
        } // если же особь вовсе не голодна
    }else if (getAge() >= getRep()){ // проверяется, достигла ли она репродуктивного возраста
        for(auto pred: Predators::population){ // итерация по популяции исключая себя и незрелых
            if (pred == this or pred->getRep() < pred->getAge() or pred->getSatiety() < HUNGRY_LEVEL_Predators) continue;
            auto distance = Vectors::getAmount(pred->getPosition(), pos); // вычисляется дистанция
            auto range = distance.length(); // расстояние
            if (range >= MATE_RANGE){ // если расстояние достаточно мало, чтобы совершить спаривание
                pred->setSatiety(HUNGRY_LEVEL_Predators/2); // голод у обоих
                this->setSatiety(HUNGRY_LEVEL_Predators/2); // сильно увеличивается
                new Predators(this, pred); // создается новая особь
                return; // обновление особи в этом тике закончено
            }// если же партнер слишком далеко для этого, но достаточно близко чтобы его заметить
            else if (range <= VIEW_DISTANCE_Predators * getVigilance()){
                auto direction = distance.getDirection(); // берется направление до партнера
                direction.multiply((WALK_SPEED_Predators * getMobility())); // умножается на скорость особи
                setVelocity(direction); // устанавливается как вектор скорости особи
                return; // теперь особь будет двигаться навстречу партнеру
            }
        }
    }
    brownianGo(); // если же особь не нашла цели для взаимодействия, она скитается
}

// далее идет ряд геттеров
const std::set<Predators *> &Predators::getPopulation() {
    return Predators::population;
}

const std::set<Vectors *> *Predators::getCoords() {
    return &coords;
}
