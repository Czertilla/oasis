cmake_minimum_required(VERSION 3.26)
project(oasis)

set(CMAKE_CXX_STANDARD 17)

add_executable(oasis main.cpp
        Vectors.cpp
        Vectors.h
        Randomizer.cpp
        constants.h
        timer.h
        Animals.cpp
        Predators.h
        Predators.cpp
        timer.cpp)
