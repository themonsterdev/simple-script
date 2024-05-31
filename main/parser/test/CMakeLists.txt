# Include the header directory in the main project
include_directories(PRIVATE "../include")

# Declaration of source files for tests
file(GLOB_RECURSE TEST_PARSER_SOURCES "*.cpp")

# Link Google Test libraries
link_libraries(gtest gtest_main parser ast)

# Add test files
add_executable(parser_test ${TEST_PARSER_SOURCES})

# Add tests to CTest
add_test(NAME parser_test COMMAND parser_test)
