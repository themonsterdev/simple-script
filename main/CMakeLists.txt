# Set the C++ standard to C++20 and require it
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add subdirectories.
add_subdirectory(ast)
add_subdirectory(compiler)
add_subdirectory(context)
add_subdirectory(interpreter)
add_subdirectory(lexer)
add_subdirectory(parser)
add_subdirectory(scope)

# Declaration of source files for tests
file(GLOB_RECURSE TEST_SOURCES "*_test.cpp")

# Add test files
add_executable(all_test ${TEST_SOURCES})

# Link Google Test libraries
target_link_libraries(all_test gtest gtest_main parser ast)

# Include the header directory in the main project
target_include_directories(all_test
PRIVATE
	"include/ast"
	"include/compiler"
	"include/context"
	"include/interpreter"
	"include/lexer"
	"include/parser"
	"include/scope"
)

# Add tests to CTest
add_test(NAME all_test COMMAND all_test)
