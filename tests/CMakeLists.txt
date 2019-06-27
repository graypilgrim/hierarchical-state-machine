file(GLOB TEST_SOURCES "*.cpp")

set (TESTS_BINARY "${BINARY_FILE}-tests")

add_executable ("${TESTS_BINARY}" "${TEST_SOURCES}")
target_link_libraries("${TESTS_BINARY}" SOURCE_OBJS)

add_custom_command(
     TARGET ${TESTS_BINARY}
     COMMENT "Run tests"
     POST_BUILD 
     COMMAND ${TESTS_BINARY}
)
