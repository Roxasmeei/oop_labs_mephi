cmake_minimum_required(VERSION 3.26)
set(CMAKE_CXX_STANDARD 20)

# Создаем библиотеку Enemy
add_library(Worker STATIC source/Worker.cpp)

# Добавляем директорию с заголовочными файлами
target_include_directories(Worker PUBLIC include)
target_link_libraries(Worker Descriptors Utils)