cmake_minimum_required(VERSION 3.26)
project(Utils)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(Assistance)
add_subdirectory(HashMap)


add_library(Utils INTERFACE)
target_include_directories(Utils INTERFACE Assistance/include HashMap/include)
target_link_libraries(Utils INTERFACE Assistance HashMap)
