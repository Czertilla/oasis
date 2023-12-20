//
// Created by Redmi on 19.12.2023.
//

#ifndef OASIS_CONSTANTS_H
#define OASIS_CONSTANTS_H 1

const double X_BORDER_World = 340.0;
const double Y_BORDER_World = 340.0;
const int X_BORDER_Screen   = 340;
const int Y_BORDER_Screen   = 340;
const int DOT_SCREEN_RADIUS = 2;

const float MAX_HEALTH_LEVEL        = 99.0;
const float MIN_HEALTH_LEVEL        = 3.1;
const float MAX_STAMINA_LEVEL       = 99.0;
const float MIN_STAMINA_LEVEL       = 3.1;
const float MB_HEALING_COST         = 0.3;
const float MB_RECUPERATION_COST    = 0.1;
const float STAMINA_LOST_SPEED      = 0.3;

const long MINUTE   = 60;
const long HOUR     = 60 * MINUTE;
const long DAY      = 24 * HOUR;
const long MONTH    = 30 * DAY;
const long YEAR     = 365 * DAY;

static float timeLineSpeed          = 1.0;

const double OLD_AGE_Animals        = YEAR* 20;
const double REP_AGE_Animals        = YEAR* 1;
constexpr float MIN_GEN_Animals     =       0.4;
constexpr float MAX_GEN_Animals     =       2.7;
const double VIEW_DISTANCE_Animals  =       20.0;
const double HUNGRY_LEVEL_Animals   =       101.0;
const double WALK_SPEED_Animals     =       1.0;
const double RUN_SPEED_Animals      =       4.5;

const double HUNGRY_LEVEL_Predators     = HUNGRY_LEVEL_Animals;
const double VIEW_DISTANCE_Predators    = VIEW_DISTANCE_Animals;
const double WALK_SPEED_Predators       = WALK_SPEED_Animals;
const double RUN_SPEED_Predators        = RUN_SPEED_Animals * 1.3;
const double KILL_RANGE                 = 1.5;

const double HUNGRY_LEVEL_Herbivores    = HUNGRY_LEVEL_Animals;
const double VIEW_DISTANCE_Herbivores   = VIEW_DISTANCE_Animals;
const double WALK_SPEED_Herbivores      = WALK_SPEED_Animals;
const double RUN_SPEED_Herbivores       = RUN_SPEED_Animals;
const double GRASS_RECOVERY             = 1.0;


#endif //OASIS_CONSTANTS_H

