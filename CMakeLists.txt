cmake_minimum_required (VERSION 3.10)
project (HierarchicalStateMachine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 --std=c++14 -Wall -Wextra -pedantic")
set(BINARY_FILE "hsm")

include_directories(${PROJECT_SOURCE_DIR}/src)

add_executable("${BINARY_FILE}" "${PROJECT_SOURCE_DIR}/src/main.cpp")

target_link_libraries("${BINARY_FILE}" SOURCE_OBJS)

add_subdirectory(src)