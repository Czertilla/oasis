add_executable(
        testbgi
        main.cpp
        graphics.h
        Herbivores.cpp
        Animals.cpp
        Predators.cpp
        Randomizer.cpp
        timer.cpp
        Vectors.cpp
)


set(CMAKE_EXE_LINKER_FLAGS "-static")
target_link_libraries(testbgi bgi)
