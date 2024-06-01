# Add header files to the library
file(GLOB_RECURSE RULE_SOURCES "*.cpp")

# Configuration of the test executable
add_executable(lexer_test ${RULE_SOURCES})

# Include the header directory in the main project
target_include_directories(lexer_test PUBLIC "../include")

# Link with the libraries
target_link_libraries(lexer_test gtest gtest_main lexer)

# Add the test to CTest
add_test(NAME lexer_test COMMAND lexer_test)
