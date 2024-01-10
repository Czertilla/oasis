//
// Created by Redmi on 18.12.2023.
//

#include "Animals.h" // заголовочный файл жтого класса
#include "Randomizer.h" // модуль рандома
#include <vector>
//  исходный файл класса Животные - родительского класса для классов Хищники и Травоядные.
//  Здесь описываются общие свойства и процессы жизнедеятельности для Хищников и Травоядных
std::set<Animals*> Animals::population{}; // популяция Животных, тут храняться указатели на ВСЕХ животных в симуляции

Animals::Animals(const Vectors& pos) {
//    конструктор для случая, когда особь искуственно выставляется на определенные координаты
    lastUpdate = timer::get(); // сразу же проставляется время, когда это было сделано (время в симуляции)
    population.insert(this);// особь записывается в симуляцию
    position = pos; // позиция записывается исходя из аргумента
    age = 0.0; // новорожденный возрастом 0
    // далее проставляются стандартные значения генов такие как
    old = OLD_AGE_Animals; // максимальный возраст (берется из файла с константами)
    rep = REP_AGE_Animals; // репродуктивный возраст (так же из констант)
    vigilance = 1.0;       // множитель даьлности видимости (как далеко особь может засечь цель)
    mobility = 1.0;        // мобильность, прямо пропорционально итоговой скорости и расходу выносливости
    endurance = 1.0;       // выносливость, обратно пропорционально расхроду выносливости
    metabolism = 1.0;      // метаболизм, прямо пропорционально расзоду сытости и пополнению шкалы выносливости
    stamina = 100.0;       // шкала, сколько сил осталось у особи (тратиться засчет расхода выносл., попол засчет голода
    health = 100.0;        // шкала здоровья, на данный момент никак не задействована
    satiety = 100.0;       // шкала сытости, расходуется засчет голода (метаболизм) пополняется засчет насыщения
    saturation = SATURATION_Animals; //насыщение от одног приема пищи
    femal = true;          // пол (является ли особь  самкой) на данной момент не задействовано, все особи Гермафродиты
    dead = false;          // выставляется, что особь жива
}

Animals::Animals(Animals* father, Animals* mother) {
//    онструктор для случая, когда новая особь рождается, отличается от перового конструктора наследованием генов
//    родителей с фактором мутации. Позиция выставляется как у мамы (вторая особь)
    lastUpdate = timer::get();
    population.insert(this);
    position = mother->getPosition();
    age = 0.0;
    // все гены (поля со значением близким к 1.0, множители на которые домнажаются те или иные значения) определяется
    // с помощью метода createGen см. 56 строку
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
    dead = false;
}


float Animals::creategen(float fatherGen, float motherGen){
//    создание гена, берется среднее арифметическое генов родителей и домножается на коэфициент мутации - случайное
//    число в заданных константами из файла с константами границах)
    return (fatherGen + motherGen) / 2 * (float) randDouble(MIN_GEN, MAX_GEN);
}

void Animals::update(){
//    метод обновления, к нему процесс симуляции возвращается каждый тик, определяется сколько времени прошло с прошлого
//    обновления и на основе этого времени обновляется инофрмация
    double currUpdate = timer::get(); // данный момент по часам симцляции
    double timeGap = timer::getGap(lastUpdate, currUpdate); // расчет сколько врмени прошло
    age += timeGap; // состариваем на это время особь
    if(age >= OLD_AGE_Animals * old){ // проверяем  не исжила ли особь свое
        this->death(); // если исжила, умерщвляем ее
        return; // на этом обновление можно завершить
    }
    auto gapVect = velocity.getMultiplied(timeGap); // умножаем вектор скорости на время, получаем
    // вектор смещения
    position.add(gapVect); // которым прибавляем к вектору позиции, актуализируя ее
    stamina -= STAMINA_LOST_SPEED * (float) (gapVect.length() * velocity.length()) / endurance; // теперь расчитаем
    // расход сил, этот расход прямо пропорционален квадрату скорости, времени и обратно пропорционален выносливости
    bool hmflag{false}, smflag{false};// два флага, обозначающие восстанавливала особь здоровье или силы
    if (health < MAX_HEALTH_LEVEL) { // условие того что особь доолжжна была восстанавливать здоровье (всегда ложь)
        hmflag = true;
        metabolism += MB_HEALING_COST;
        health += metabolism * (float) timeGap;
    }
    if (stamina < MIN_STAMINA_LEVEL) velocity = Vectors(0, 0); // если силы закончились, особь должжна перестать
    // двигаться

//    health += effects.count("healing")  * (old - age) / age ;
//    if (health < 100.0 and effects.count("healing") == 0){
//        effects["healing"] = -1;
//        metabolism += 0.5;
//    }
    if (stamina < MAX_STAMINA_LEVEL){ // если силы меньше определенного порога, нужно начать их восстанавливать
        smflag = true; // проставляем флаг
        metabolism += MB_RECUPERATION_COST; // увеличиваем метаболизм на константу из файла констант
        stamina += metabolism * (float) timeGap;   // восстанавливаем шкалу силы, так сильно, какой сильный метаболизм
    }
    satiety -= (float)this->HUNGER_SPEED * metabolism * (float)timeGap; // расходуем сытость  учитывая увеличенный
    // метаболизм (или  не увеличенный если особь не восстанавливала силы)
    if(satiety <= 0.0){ // проверяем особь на смерть от голода
        this->death();
        return;
    }
    if(hmflag) metabolism -= MB_HEALING_COST; // возвращаем изначальное значение метаболизма с помощью флагов
    if(smflag) metabolism -= MB_RECUPERATION_COST;
    // возвращаем в границы симуляции, если особь за них вышла:
    if(position.x > X_BORDER_World) position.x = X_BORDER_World;
    if(position.x < -X_BORDER_World) position.x = - X_BORDER_World;
    if(position.y > Y_BORDER_World) position.y = Y_BORDER_World;
    if(position.y < -Y_BORDER_World) position.y = - Y_BORDER_World;
    lastUpdate = currUpdate; // перезаписываем новое время последнего оновления
}

void Animals::brownianGo() {
//    метод задает случайный вектор скорости если особь стояла на месте, либо слегка корректирует уже имеющийся вектор
    if (velocity.length() == 0){
        velocity = Vectors(randDouble(-1, 1), randDouble(-1, 1)).getDirection();
        // создаем новый вектор с помощью двух рандомных координат, превращаем его в едениный с помощью метода
        // getDirection
    }
    else {
        // если особь уже двигалась
        auto direction = velocity.getDirection();
        auto x{direction.x}, y{direction.y}; // берем координаты вектора скорости
        float RB = 0.0212; // задаем радиус окрестности в которой можно изменять координаты
        velocity.x += randDouble(-RB + x, RB + x); // изменяем координаты взяв случайное число в данной
        velocity.y += randDouble(-RB + y, RB + y); // окрестности изначальных коорднат
        velocity = direction.getDirection(); // приводим значение вектора скорости к общему виду перед домножением
    }
    velocity.multiply(WALK_SPEED * mobility); // домножаем еденичный вектор направления скорости на скорость
    // ходьбы, взятой в соответсвтие с классом особи из файла с константами, модифицированную геном мобильности
}

void Animals::eat() {
    // изменение полей особи в зависимости от гена насыщения
    satiety += saturation;
    if (satiety > 100.0) satiety = 100.0; // ограничение шкалы сытости верхней границей в 100
}

void Animals::death(){
    // изменения связанные со гибелью особи
    health = 0.0; //  обнуление здоровья
    population.erase(this); // исключение из популяции
    dead = true;    // закрепление факта гибели в соответсвующем поле
}


// далее идут геттеры и сеттеры для получения доступа к приватным полям класса
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

const std::set<Animals *> &Animals::getPopulation() {
    return population;
}

bool Animals::isDead() const {
    return dead;
}

void Animals::setSatiety(float sat) {
    Animals::satiety = sat;
}

const Vectors &Animals::getVelocity() const {
    return velocity;
}

