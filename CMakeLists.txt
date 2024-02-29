cmake_minimum_required(VERSION 3.0.0)
project(MyEvolutionSim2)

set(SourceFiles
    Headers/Vector2/Vector2.hpp
    Src/Vector2/Vector2.cpp
    main.cpp)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SourceFiles})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})