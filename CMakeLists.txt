#Cmake version
cmake_minimum_required(VERSION 3.0.0)

#Project Name
project(MyEvolutionSim2)

#Set build binary in build/bin folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/bin)

#Get all headers and sources files
file(GLOB_RECURSE SourceFiles "Headers/*.hpp" "Src/*.cpp")

#Add main.cpp file
set(mainFile main.cpp)

#Search for SDL2 libraries, set it mandatory and include all directories
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

#Add to the executagle the project name, all source files and main.cpp file
add_executable(${PROJECT_NAME} ${SourceFiles} ${mainFile} ${utilsFile})

#Link SDL2 libraries to project
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})