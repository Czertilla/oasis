//
// Created by Redmi on 19.12.2023.
//
//  Заголовочный файл с константами. Параметры с помощью которых можно гибко настроить работу симуляции

#ifndef OASIS_CONSTANTS_H
#define OASIS_CONSTANTS_H 1
const long START_COUNT_Predators    = 10;   // Начальное количество Хищников
const long START_COUNT_Herbivores   = 750;  // Начальное количество Травоядных
const long START_COUNT_Grass        = 456;  // Начальное количество Травы

const double X_BORDER_World = 340.0;    // Максимальная координата X в симуляции (линейный размер в два раза больше)
const double Y_BORDER_World = 340.0;    // Максимальная координата Y
const int X_BORDER_Screen   = 340;      // Подобный коэффициент, но для экрана отображения (лучше оставлять равным)
const int Y_BORDER_Screen   = 340;      // Размер экрана по Y
const int DOT_SCREEN_RADIUS = 2;        // Радиус точки, обозначающий объект
const int TEXT_HEIGHT       = 15;       // Размер шрифта информации
const int STRINGS_COUNT    = 1;         // Количества строк информации

const float MAX_HEALTH_LEVEL        = 99.0; // Максимальный уровень здоровья
const float MIN_HEALTH_LEVEL        = 3.1;  // Минимальный уровень здоровья
const float MAX_STAMINA_LEVEL       = 99.0; // Максимальный уровень сил
const float MIN_STAMINA_LEVEL       = 3.1;  // минимальный уровень сил
const float MB_HEALING_COST         = 0.3;  // коэффициент увеличения метаболизма во время лечения
const float MB_RECUPERATION_COST    = 0.1;  // коэффициент увеличения метаболизма во время восстановления сил
const float STAMINA_LOST_SPEED      = 0.3;  // Стандартное значения скорости расхода сил [ед./сек.]
// далее, тк все время внутри симуляции измеряется в секундах, для удобства обозначены другие единицы измерения времени
const long MINUTE   = 60;           // минута
const long HOUR     = 60 * MINUTE;  // час
const long DAY      = 24 * HOUR;    // день
const long MONTH    = 30 * DAY;     // месяц (все месяцы приведены к 30 дням)
const long YEAR     = 365 * DAY;    // год (все года считаются невисокосными)

static float timeLineSpeed          = 10.0; // скорость течения времени относительно реального времени

const double OLD_AGE_Animals        = MINUTE* 0.13; // стандартное значение максимального возраста для Животных [сек.]                                                                       ;
const double REP_AGE_Animals        = MINUTE* 0.1;  // стандартное значение репродуктивного возраста для Животных [сек.]
constexpr float MIN_GEN_Animals     =       0.4;    // минимальный фактор мутации
constexpr float MAX_GEN_Animals     =       2.7;    // максимальный фактор мутации
const double VIEW_DISTANCE_Animals  =       50.0;   // стандартное значения дальности зрения Животных
const double HUNGRY_LEVEL_Animals   =       90.0;   // стандартное значение шкалы сытости наступления голода у Животных
const double WALK_SPEED_Animals     =       1.0;    // стандартное значение скорости спокойной ходьбы у Животных [м/с]
const double RUN_SPEED_Animals      =       4.5;    // стандартное значение скорости бега у Животных [м/с]
const double MATE_RANGE             =       0.5;    // значение максимального расстояния для спаривания у Животных [м]
const double HUNGER_SPEED_Animals   =       0.01;   // скорость расхода шкалы сытости у животных [ед./сек.]
const double SATURATION_Animals     =       100.0;  // стандартное значение насыщения от трапезы у Животных

const double VIEW_DISTANCE_Predators                = VIEW_DISTANCE_Animals;    // то же что 40 стрк., но у Хищников
const double HUNGRY_LEVEL_Predators                 = HUNGRY_LEVEL_Animals;     // то же что 41 стрк., но у Хищников
const double WALK_SPEED_Predators                   = WALK_SPEED_Animals;       // то же что 42 стрк., но у Хищников
const double RUN_SPEED_Predators                    = RUN_SPEED_Animals * 1.3;  // то же что 43 стрк., но у Хищников
const double KILL_RANGE                             = 1.5;                      // расстояние для поимки жертвы
const double HUNGER_SPEED_Predators                 = HUNGER_SPEED_Animals;     // то же что 45 стрк., но у Хищников
const double SATURATION_Predators                   = 14.5;                     // то же что 46 стрк., но у Хищников

const double VIEW_DISTANCE_Herbivores               = VIEW_DISTANCE_Animals;      // то же что 40 стрк., но у Травоядных
const double HUNGRY_LEVEL_Herbivores                = HUNGRY_LEVEL_Animals;       // то же что 41 стрк., но у Травоядных
const double WALK_SPEED_Herbivores                  = WALK_SPEED_Animals;         // то же что 42 стрк., но у Травоядных
const double RUN_SPEED_Herbivores                   = RUN_SPEED_Animals;          // то же что 43 стрк., но у Травоядных
const double GRASS_RECOVERY                         = 0.6;                        // процент восстановления травы
const double HUNGER_SPEED_Herbivores                = HUNGER_SPEED_Animals * 1.23;// то же что 45 стрк., но у Травоядных
const double GRASS_FREQUENCY                        = MINUTE * 0.1;               // частота обновления травы [сек.]
const double SATURATION_Herbivores                  = 100.0;                      // то же что 46 стрк., но у Травоядных


#endif //OASIS_CONSTANTS_H

