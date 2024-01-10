//
// Created by MacBook Pro on 20.12.2023.
//

#include "Herbivores.h" // заголовочный файл данного класса
#include "Randomizer.h" // модуль рандома
// это исходный файл класса Травоядные, здесь описаны уникальные для травоядных особенности, наследуется от класса
// Животные (см. файл Animals.cpp)
std::set<Herbivores*> Herbivores::population{}; // популяция травоядных, множество всех травоядных (без хищников)
std::set<Vectors*> Herbivores::grass{}; // множество координат,где находятся трава, храниться как статическое поле
std::set<Vectors*> Herbivores::coords{}; // множество указателей координат всех особей, для отображения на экран
double Herbivores::lastUpdate = 0.0; // время последнего обновления травы (не путать с таким же полем класса Животные)

Herbivores::Herbivores(Animals* father, Animals* mother): Animals(father, mother) {
//    конструктор класса Травоядные для случая, когда особь выставляется вручную на координаты, наследует соответсвующий
//    конструктор класса Животные
    Animals::HUNGER_SPEED = HUNGER_SPEED_Herbivores; // выставляется уникальный для этого класса множитель голода
    coords.insert(&position); // множество координат класса пополняется указателем на вектор позиции особи
    Animals::WALK_SPEED = WALK_SPEED_Herbivores; // устанавливается уникальная для класса скорость ходьбы в поле,
    // относящееся к родительскому классу
    Herbivores::population.insert(this); // добавляем указатель на особь в популяцию отдельно травоядных
    setSatiety((float)HUNGRY_LEVEL_Herbivores); // устанавливаем уникальное для этого класса значение сытости в поле,
    // относящееся к родительскому классу
}

Herbivores::Herbivores(const Vectors &position): Animals(position) {
    //второй конструктор для случая, когда особь появляется от спаривания двух других особей, наследует соответсвующий
    // конструктор родительсткого класса.
    Animals::HUNGER_SPEED = HUNGER_SPEED_Herbivores;
    coords.insert(&this->position);
    Animals::WALK_SPEED = WALK_SPEED_Herbivores;
    Herbivores::population.insert(this);
}

void Herbivores::death() {
//    метод вызываемый в случае гибели особи класса Травоядные
    Herbivores::population.erase(this); // особь исключается из популяции Травоядных
    Herbivores::coords.erase(&position); // уберется указатель на позицию для прекращения отображения на экране
    Animals::death(); // вызывается соответсвующий метод родительского класса
}

void Herbivores::updateGrass() {
//    статический метод для обновления травы, вызывается в конце каждого тика симуляции
    auto currTime = timer::get(); // определяем текущее время
    if (currTime - lastUpdate >= GRASS_FREQUENCY){ // проверяем, прошло ли достаточно времени для обновления травы
        // соответсвующую константу можно выставить в файле с константами
        lastUpdate = currTime; // обновляется время последнего обновления травы
        auto count = grass.size(); // определяется, сколько в данный момент травы в симуляции
        // количество травы, которое нужно высадить прямо пропорционально отношению изначального количества травы к
        // нынешнему, а также прямо пропорционально отношению популяции травоядных в данный момент к изначальному
        // количеству, от этого числа берется процент восстановления травы, выставляемый в файле с константами
        for (int i=0; i < (int)(START_COUNT_Grass * GRASS_RECOVERY/(float)count
                                * population.size()/START_COUNT_Herbivores); i++) {
            Herbivores::addGrass(); // полученое количество раз вызывается перегрузка метода без аргументов добавления
            // травы. Эта перегрузка выставляет траву на рандомные координаты
        }
        Herbivores::addGrass(); // в любом случае выставляется одна травинка если время обновления прошло
    }
}


void Herbivores::addGrass() {
    // перегрузка метода выставления травы. Без аргументов этот метод берет рандомные координаты
    grass.insert(new Vectors(randDouble(-X_BORDER_World, X_BORDER_World),
                             randDouble(-Y_BORDER_World, Y_BORDER_World)));
}

void Herbivores::addGrass(Vectors* pos) {
    Herbivores::grass.insert(pos); // выставление травы на заданные координаты
}


void Herbivores::eraseGrass(Vectors* gr) {
    Herbivores::grass.erase(gr); // метод убирает координаты по указателю на найденную травоядным траву (координаты)
}

void Herbivores::update() {
    // перегрузка родительского метода обновления информации об особь. Он описывает взаимодействие особи со средой
    Animals::update(); // в начале вызывается родительский метод
    auto pos = getPosition().getMultiplied(-1); // берется обратный вектор позиции особи, для
    // дальнейшего складывания его с другими радиус-векторами и нахождения расстояния и направления до объектов
    // в первую очередь особь ищет вокруг себя опасность в виде хищников, это не всегда ближайший хищник, таким образом
    // мы получаем естественную нерациональность и оптимизацию процесса симуляции
    for (auto pred : *Predators::getCoords()){ // берется множество координат хищников с помощью геттера
        auto distance = Vectors::getAmount(*pred, pos); // вычисляется вектор дистанции до хищника
        auto range = distance.length(); // находится расстояние до хищника, как модуль вектора дистанции
        if (range <= VIEW_DISTANCE_Herbivores * getVigilance()){ // видит ли хищника травоядное (ген дальности видимости
            auto direction = distance.getDirection(); // определяется направление к хищнику
            direction.multiply(-1 * RUN_SPEED_Herbivores * getMobility()); // направление меняется на обратное
            setVelocity(direction); // теперь особь бежит в обратном направлении так быстро, как ему позволяют гены
            return; // больше особь ничего не интересует, ей нужно убегать от хищника
        }
    } // если хищников поблизости не обнаружено, процесс идет дальше
    if (this->getSatiety() < HUNGRY_LEVEL_Herbivores){ // проверка на голод. Если сытость ниже отметки особь ищет еду
        for(auto grass : *Herbivores::getGrass()){ // итерируется по всем координатам травы
            auto distance = Vectors::getAmount(*grass, pos); // похожим на остальные образом вычисляется
            auto range = distance.length(); // дистанция и расстояние, проверяется способна ли особь заметить
            if (range <= KILL_RANGE){ // если трава достаточно близко чтобы ее съесть, особь ее съедает
                eraseGrass(grass);
                eat();
                break;
            }
            else if (range <= VIEW_DISTANCE_Herbivores * getVigilance()){ // если же трава достаточно, чтобы ее заметить
                auto direction = distance.getDirection(); // выставляется вектор скорости по направлению к траве
                direction.multiply(WALK_SPEED_Herbivores * getMobility());
                setVelocity(direction); // сеттер скорости
                return;
            }
        }
    } // если же особь не смогла найти еду или она не голодна, она будет пытаться найти особь для спаривания
    if (getAge() >= getRep()){ // теперь проверяется, достигла ли особь репродуктивного возраста
        for(auto herb: Herbivores::population){ // походим образом ищется подходящая особь для спаривания
            if (herb == this or herb->getRep() < herb->getAge()) continue; // пропускаем маленьких и себя
            auto distance = Vectors::getAmount(herb->getPosition(), pos);
            auto range = distance.length();
            if (range >= MATE_RANGE){ // достаточно ли близко особь для спаривания
                herb->setSatiety(herb->getSatiety() - 6); // спаривание тратит фиксированное значение сытости
                this->setSatiety(getSatiety() - 6); //  у обоих особей
                new Herbivores(this, herb); // вызывается конструктор Класса травоядных
                break; // цикл прерывается
            }
            else if (range <= VIEW_DISTANCE_Herbivores * getVigilance()){ // если особь далеко для спаривания, но видно
                auto direction = distance.getDirection(); // устанавливаем направление движения ей навстречу
                direction.multiply((WALK_SPEED_Herbivores * getMobility()));
                setVelocity(direction);
                return; // больше особь ничего не интересует ей надо спариться
            }
        }
    } // и только теперь, если особь не нашла ни опасности ни партнера, она ищет еду
    brownianGo();
}

// далее идет ряд геттеров и сеттеров
const std::set<Vectors *> *Herbivores::getCoords() {
    return &coords;
}

const std::set<Vectors *> *Herbivores::getGrass() {
    return &Herbivores::grass;
}

const std::set<Herbivores *> &Herbivores::getPopulation() {
    return Herbivores::population;
}
