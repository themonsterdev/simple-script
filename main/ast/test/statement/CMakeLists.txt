# Declaration of source files for tests
file(GLOB TEST_SOURCES "*.cpp")

# Add test files
add_executable(all_statement_test ${TEST_SOURCES})
add_executable(assignment_statement_test assignment_statement_test.cpp)
add_executable(print_statement_test print_statement_test.cpp)
add_executable(var_declaration_statement_test var_declaration_statement_test.cpp)

# Add tests to CTest
add_test(NAME all_statement_test COMMAND all_statement_test)
add_test(NAME assignment_statement_test COMMAND assignment_statement_test)
add_test(NAME print_statement_test COMMAND print_statement_test)
add_test(NAME var_declaration_statement_test COMMAND var_declaration_statement_test)
