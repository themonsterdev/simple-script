# Include the header directory in the main project
include_directories(PRIVATE "../include")

# Declaration of source files for tests
file(GLOB TEST_PARSER_SOURCES "*.cpp")

# Link Google Test libraries
link_libraries(gtest gtest_main parser ast)

# Add test files
add_executable(all_parser_test ${TEST_PARSER_SOURCES})
add_executable(parser_test parser_test.cpp main_test.cpp)

# Add tests to CTest
add_test(NAME all_parser_test COMMAND all_parser_test)
add_test(NAME parser_test COMMAND parser_test)
