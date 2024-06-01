# Declaration of source files for tests
file(GLOB_RECURSE TEST_SOURCES "*.cpp")

# Add test files
add_executable(parser_test ${TEST_SOURCES})

# Link Google Test libraries
target_link_libraries(parser_test gtest gtest_main parser ast)

# Include the header directory in the main project
target_include_directories(parser_test PRIVATE "../include")

# Add tests to CTest
add_test(NAME parser_test COMMAND parser_test)
