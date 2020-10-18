cmake_minimum_required(VERSION 3.0.0)
project(Pokemon-battle-sim VERSION 1.1.0)

include(CTest)
enable_testing()

file(GLOB SOURCES
    src/*.h
    src/*.cpp
)

add_executable(Pokemon-battle-sim ${SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# SET(TARGET_HPP
#     main.hpp
#     move.hpp
#     pokemon.hpp
#     trainer.hpp)
# SET(TARGET_SRC
#     move.cpp
#     pokemon.cpp
#     trainer.cpp
#     )

# add_library(mainH src/main.hpp)
# add_library(MoveH src/move.hpp)
# add_library(PokemonH src/pokemon.hpp)
# add_library(TrainerH src/trainer.hpp)
# add_library(Move src/move.cpp)
# add_library(Pokemon src/pokemon.cpp)
# add_library(Trainer src/trainer.cpp)

# add_executable(Pokemon-battle-sim src/main.cpp)