cmake_minimum_required(VERSION 3.12)
project(Three)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)
include(GoogleTest)

# Добавление исполняемого файла
add_executable(three
    src/main.cpp
    src/three.cpp
    src/three.h
)

add_executable(test_three
    test/test_three.cpp
    src/three.cpp
    src/three.h
)

# Связывание тестов с Google Test
target_link_libraries(test_three GTest::GTest GTest::Main)

# Добавление тестов в CTest
gtest_discover_tests(test_three)

# Настройка компилятора
target_compile_features(three PRIVATE cxx_std_14)
target_compile_options(three PRIVATE -Wall -Wextra -Wpedantic)
target_compile_features(test_three PRIVATE cxx_std_14)
target_compile_options(test_three PRIVATE -Wall -Wextra -Wpedantic)