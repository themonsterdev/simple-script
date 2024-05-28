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
