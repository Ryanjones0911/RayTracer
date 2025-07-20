cmake_minimum_required(VERSION 3.31)
project(RayTracer)

set(CMAKE_CXX_STANDARD 20)

add_executable(RayTracer Src/main.cpp Src/tuple.cpp Src/Canvas.cpp
)

# ----------- GoogleTest Setup --------------
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/release-1.12.1.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_library(tuple_lib Src/tuple.cpp)

# Add a single test target that includes all test source files
add_executable(all_tests
        Tests/tupleTests.cpp
        Src/canvas.cpp
        Include/canvas.h
        Tests/canvasTests.cpp

)

target_link_libraries(all_tests gtest_main tuple_lib)

add_test(NAME all_tests COMMAND all_tests)