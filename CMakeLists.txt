cmake_minimum_required(VERSION 3.16)
project(three_ternary LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Library
add_library(three
    src/Three.cpp
)

target_include_directories(three PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Demo executable
add_executable(three_app src/main.cpp)

target_link_libraries(three_app PRIVATE three)

# Testing setup
include(FetchContent)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(three_tests
    tests/ThreeTests.cpp
)

target_link_libraries(three_tests PRIVATE three GTest::gtest GTest::gtest_main)
include(GoogleTest)

gtest_discover_tests(three_tests)
