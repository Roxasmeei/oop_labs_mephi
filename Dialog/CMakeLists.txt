cmake_minimum_required(VERSION 3.26)
project(Dialog)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(Dialog source/main.cpp source/Menu.cpp source/BuildingApp.cpp)

target_link_libraries(Dialog WorkerTypes Brigade)