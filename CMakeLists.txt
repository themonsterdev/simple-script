# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.27)

# Set the project name
project(simple-script)

# Include the test configuration file
include(cmake/test.cmake)

# Add the 'main' subdirectory where the main project code resides
add_subdirectory(main)
