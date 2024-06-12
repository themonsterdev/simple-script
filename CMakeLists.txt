# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.27)

# Set the project name
project(simple-script)

# Set the C++ standard to C++20 and require it
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include the test configuration file
include(cmake/test.cmake)

# Add header files to the library
file(GLOB_RECURSE INTERPRETER_SOURCES "source/*.cpp")

# Create an executable for the interpreter
add_executable(interpreter ${INTERPRETER_SOURCES})

# Include the header directory in the project
target_include_directories(interpreter PUBLIC "include")

# Add subdirectories.
add_subdirectory(test)
