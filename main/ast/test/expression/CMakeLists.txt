# Declaration of source files for tests
file(GLOB TEST_SOURCES "*.cpp")

# Add test files
add_executable(all_expression_test ${TEST_SOURCES})
add_executable(string_operator_expression_test string_operator_expression_test.cpp)

# Add tests to CTest
add_test(NAME all_expression_test COMMAND all_expression_test)
add_test(NAME string_operator_expression_test COMMAND string_operator_expression_test)
