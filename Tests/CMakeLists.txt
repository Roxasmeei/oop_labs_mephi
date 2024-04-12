cmake_minimum_required(VERSION 3.26)

project(Tests)

set(CMAKE_CXX_STANDARD 20)

if (UNIX)
    set(gtest_source_url https://github.com/google/googletest/archive/release-1.11.0.tar.gz)
elseif (WIN32)
    set(gtest_source_url https://github.com/google/googletest/archive/release-1.11.0.zip)
else ()
    message(FATAL_ERROR "Operating system isn't supported")
endif ()


include(FetchContent)
FetchContent_Declare(
        googletest
        URL ${gtest_source_url}
)

FetchContent_MakeAvailable(googletest)

enable_testing()


add_executable(Tests source/main.cpp
        source/TestCase_descriptors.cpp
        source/TestCase_WorkerTypes.cpp

)

# Добавляем библиотеки, первые две нужны для работы с google test, так же добавляем к проекту библиотеку Locker, которую будем тестировать
target_link_libraries(Tests gtest
        gtest_main
        Descriptors
        WorkerTypes)