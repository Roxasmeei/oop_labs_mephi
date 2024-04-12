cmake_minimum_required(VERSION 3.26)
set(CMAKE_CXX_STANDARD 20)

# Создаем библиотеку Enemy
add_library(ContributingWorker STATIC source/ContributingWorker.cpp)

# Добавляем директорию с заголовочными файлами
target_include_directories(ContributingWorker PUBLIC include)
target_link_libraries(ContributingWorker Descriptors Worker)