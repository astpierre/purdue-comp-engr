cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)

project(zork)

add_library(zorklib
    include/Container.h
    include/Component.h
    include/Trigger.h
    include/Condition.h
    include/Creature.h
    include/Room.h
    include/Item.h
    include/Game.h
    include/tinyxml2.h
    src/tinyxml2.cpp
    src/Container.cpp
    src/Component.cpp
    src/Condition.cpp
    src/Trigger.cpp
    src/Creature.cpp
    src/Room.cpp
    src/Item.cpp
    src/Game.cpp
)

target_include_directories(
  zorklib
  PUBLIC
    "include"
)

add_executable(zork_test
  src/main.cpp
)

target_link_libraries(zork_test zorklib)
