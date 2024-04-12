cmake_minimum_required(VERSION 3.26)
set(CMAKE_CXX_STANDARD 20)

# Создаем библиотеку Enemy
add_library(Assistance STATIC source/Utils.cpp)

# Добавляем директорию с заголовочными файлами
target_include_directories(Assistance PUBLIC include)
#target_link_libraries(Assistance Descriptors Utils)