cmake_minimum_required(VERSION 3.20.0)
project(loglens VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(loglens
    src/main.cpp
    src/parser.cpp
    src/analyzer.cpp
    src/report.cpp
)

target_include_directories(loglens PRIVATE include)

if (MSVC)
    target_compile_options(loglens PRIVATE /W4 /WX)
else()
    target_compile_options(loglens PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

include(CTest)

enable_testing()

find_package(GTest REQUIRED)

add_executable(loglens_tests
    tests/parser_tests.cpp
    src/parser.cpp
)

target_include_directories(loglens_tests PRIVATE include)

target_link_libraries(loglens_tests
    PRIVATE
        GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(loglens_tests)
