# Declaration of source files for tests
file(GLOB_RECURSE TEST_SOURCES "*.cpp")

# Add test files
add_executable(ast_test ${TEST_SOURCES})

# Link Google Test libraries
target_link_libraries(ast_test gtest gtest_main ast context value)

# Include the header directory
target_include_directories(ast_test PUBLIC "../include")

# Add tests to CTest
add_test(NAME ast_test COMMAND ast_test)
