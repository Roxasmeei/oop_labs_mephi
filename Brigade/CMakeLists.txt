cmake_minimum_required(VERSION 3.26)
set(CMAKE_CXX_STANDARD 20)

# Создаем библиотеку Enemy
add_library(Brigade STATIC source/Brigade.cpp)

# Добавляем директорию с заголовочными файлами
target_include_directories(Brigade PUBLIC include)

target_link_libraries(Brigade Utils WorkerTypes WorkingSite)