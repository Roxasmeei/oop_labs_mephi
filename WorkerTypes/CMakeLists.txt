cmake_minimum_required(VERSION 3.26)
project(WorkerTypes)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(Worker)
add_subdirectory(ContributingWorker)
add_subdirectory(BrigadeLeader)


add_library(WorkerTypes INTERFACE)
target_include_directories(WorkerTypes INTERFACE include)
target_link_libraries(WorkerTypes INTERFACE Worker ContributingWorker BrigadeLeader)
