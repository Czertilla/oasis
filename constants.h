//
// Created by Redmi on 19.12.2023.
//

#ifndef OASIS_CONSTANTS_H
#define OASIS_CONSTANTS_H 1

const float MAX_HEALTH_LEVEL        = 99.0;
const float MIN_HEALTH_LEVEL        = 3.1;
const float MAX_STAMINA_LEVEL       = 99.0;
const float MIN_STAMINA_LEVEL       = 3.1;
const float MB_HEALING_COST         = 0.3;
const float MB_RECUPERATION_COST    = 0.1;

const long MINUTE   = 60;
const long HOUR     = 60 * MINUTE;
const long DAY      = 24 * HOUR;
const long MONTH    = 30 * DAY;
const long YEAR     = 365 * DAY;

static float timeLineSpeed          = 1.0;

const double OLD_AGE_Animals        = YEAR* 20;
const double REP_AGE_Animals        = YEAR* 1;
constexpr float MIN_GEN_Animals     =       0.8;
constexpr float MAX_GEN_Animals     =       2.7;
const double VIEW_DISTANCE_Animals  =       10.0;


#endif //OASIS_CONSTANTS_H

