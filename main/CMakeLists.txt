# Set the C++ standard to C++20 and require it
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add subdirectories for the compiler, interpreter, lexer, and parser
add_subdirectory(compiler)
add_subdirectory(interpreter)
add_subdirectory(lexer)
add_subdirectory(parser)
