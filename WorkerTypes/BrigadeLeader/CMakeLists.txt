cmake_minimum_required(VERSION 3.26)
set(CMAKE_CXX_STANDARD 20)

# Создаем библиотеку Enemy
add_library(BrigadeLeader STATIC source/BrigadeLeader.cpp)

# Добавляем директорию с заголовочными файлами
target_include_directories(BrigadeLeader PUBLIC include)
target_link_libraries(BrigadeLeader Worker ContributingWorker)