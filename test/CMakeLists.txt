# Declaration of source files for tests
file(GLOB_RECURSE TEST_SOURCES "*_test.cpp")

file(GLOB_RECURSE AST_SOURCES     "../source/ast/*.cpp")
file(GLOB_RECURSE CONTEXT_SOURCES "../source/context/*.cpp")
file(GLOB_RECURSE LEXER_SOURCES   "../source/lexer/*.cpp")
file(GLOB_RECURSE PARSER_SOURCES  "../source/parser/*.cpp")
file(GLOB_RECURSE SCOPE_SOURCES   "../source/scope/*.cpp")
file(GLOB_RECURSE TYPE_SOURCES    "../source/type/*.cpp")
file(GLOB_RECURSE VALUE_SOURCES   "../source/value/*.cpp")

# Add test files
add_executable(all_test
	${TEST_SOURCES}
	${AST_SOURCES}
	${CONTEXT_SOURCES}
	${LEXER_SOURCES}
	${PARSER_SOURCES}
	${SCOPE_SOURCES}
	${TYPE_SOURCES}
	${VALUE_SOURCES}
)

# Link Google Test libraries
target_link_libraries(all_test gtest gtest_main)

# Include the header directory in the test
target_include_directories(all_test PRIVATE "../include")

# Add tests to CTest
add_test(NAME all_test COMMAND all_test)
