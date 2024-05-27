# Include the header directory in the main project
include_directories(PRIVATE ../include)

# Declaration of source files for tests
file(GLOB TEST_PARSER_SOURCES "*.cpp")
file(GLOB TEST_AST_SOURCES "ast/*.cpp")

# Link Google Test libraries
link_libraries(gtest gtest_main parser)

# Add test files
add_executable(all_parser_test ${TEST_PARSER_SOURCES} ${TEST_AST_SOURCES})
add_executable(arithmetic_operator_node_test ast/arithmetic_operator_node_test.cpp main_test.cpp)
add_executable(assignment_node_test ast/assignment_node_test.cpp main_test.cpp)
add_executable(print_statement_node_test ast/print_statement_node_test.cpp main_test.cpp)
add_executable(string_operator_node_test ast/string_operator_node_test.cpp main_test.cpp)
add_executable(var_declaration_node_test ast/var_declaration_node_test.cpp main_test.cpp)
add_executable(context_test context_test.cpp main_test.cpp)
add_executable(scope_test scope_test.cpp main_test.cpp)
add_executable(parser_test parser_test.cpp main_test.cpp)

# Add tests to CTest
add_test(NAME all_parser_test COMMAND all_parser_test)
add_test(NAME arithmetic_operator_node_test COMMAND arithmetic_operator_node_test)
add_test(NAME assignment_node_test COMMAND assignment_node_test)
add_test(NAME print_statement_node_test COMMAND print_statement_node_test)
add_test(NAME string_operator_node_test COMMAND string_operator_node_test)
add_test(NAME var_declaration_node_test COMMAND var_declaration_node_test)
add_test(NAME context_test COMMAND context_test)
add_test(NAME scope_test COMMAND scope_test)
add_test(NAME parser_test COMMAND parser_test)
