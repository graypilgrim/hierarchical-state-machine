file(GLOB TEST_SOURCES "*.cpp")

set (TESTS_BINARY "${BINARY_FILE}-tests")

add_library(TEST_OBJS ${TEST_SOURCES})
add_executable ("${TESTS_BINARY}" "${PROJECT_SOURCE_DIR}/tests/tests-main.cpp")

target_link_libraries("${TESTS_BINARY}" TEST_OBJS)