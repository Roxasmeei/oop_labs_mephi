cmake_minimum_required(VERSION 3.26)
project(DescriptorsSubDir)

set(CMAKE_CXX_STANDARD 20)

# Создаем библиотеку Logic
add_library(Descriptors INTERFACE)

# Добавляем директорию с заголовочными файлами
target_include_directories(Descriptors INTERFACE include connect)

target_link_libraries(Descriptors INTERFACE)