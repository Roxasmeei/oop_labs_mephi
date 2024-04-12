cmake_minimum_required(VERSION 3.26)
set(CMAKE_CXX_STANDARD 20)

# Создаем библиотеку Enemy
add_library(WorkingSite STATIC source/WorkingSite.cpp)

# Добавляем директорию с заголовочными файлами
target_include_directories(WorkingSite PUBLIC include)

target_link_libraries(WorkingSite Utils WorkerTypes Brigade)