# Configuration of the test executable
add_executable(lexer_rules_test lexer_rules_test.cpp)
add_executable(lexer_test lexer_test.cpp)

# Include the header directory in the main project
target_include_directories(lexer_rules_test PUBLIC "../include")
target_include_directories(lexer_test PUBLIC "../include")

# Link with the libraries
target_link_libraries(lexer_rules_test gtest gtest_main lexer)
target_link_libraries(lexer_test gtest gtest_main lexer)

# Add the test to CTest
add_test(NAME lexer_rules_test COMMAND lexer_rules_test)
add_test(NAME lexer_test COMMAND lexer_test)
