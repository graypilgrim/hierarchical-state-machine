cmake_minimum_required (VERSION 3.10)
project (HierarchicalStateMachine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 --std=c++17 -Wall -Wextra -pedantic")
set(BINARY_FILE "hsm")

include_directories(${PROJECT_SOURCE_DIR}/src)

add_subdirectory(src)
add_subdirectory(tests)