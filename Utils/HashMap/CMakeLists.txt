cmake_minimum_required(VERSION 3.26)
project(HashMap)

set(CMAKE_CXX_STANDARD 20)

# Создаем библиотеку Logic
add_library(HashMap INTERFACE)

# Добавляем директорию с заголовочными файлами
target_include_directories(HashMap INTERFACE include)

#target_link_libraries(Logic INTERFACE Utils Creatures)