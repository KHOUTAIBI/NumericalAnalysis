cmake_minimum_required(VERSION 3.2)
project(climate)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
add_definitions(-std=c++17 -Wall -O2 -pedantic)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Python3 COMPONENTS Interpreter Development REQUIRED)


include_directories(
    /usr/local/include/eigen3   
    ${Python3_INCLUDE_DIRS}     
)


add_executable(${PROJECT_NAME} climate.cpp
euler.cpp
)

target_link_libraries(climate PRIVATE ${Python3_LIBRARIES})
