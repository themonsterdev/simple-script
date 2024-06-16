# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.27)

# Set the project name
project(simple-script VERSION 1.0.0)

# Set the C++ standard to C++20 and require it
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Set default build type to Debug if not specified
set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)

# Set installation prefix
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/build CACHE PATH "Installation Directory" FORCE)

# Detect platform and set compilers
if(APPLE)
    set(CMAKE_OSX_ARCHITECTURES "arm64" CACHE STRING "OS Architectures" FORCE)
    set(CMAKE_C_COMPILER "/usr/bin/clang" CACHE FILEPATH "C compiler" FORCE)
    set(CMAKE_CXX_COMPILER "/usr/bin/clang++" CACHE FILEPATH "C++ compiler" FORCE)
elseif(WIN32)
    set(CMAKE_C_COMPILER "cl.exe" CACHE FILEPATH "C compiler" FORCE)
    set(CMAKE_CXX_COMPILER "cl.exe" CACHE FILEPATH "C++ compiler" FORCE)
endif()

# Set make program for Ninja
set(CMAKE_MAKE_PROGRAM "/opt/homebrew/bin/ninja" CACHE FILEPATH "Make program" FORCE)

# Options de configuration
option(BUILD_TESTS "Build the tests" OFF)

# Add subdirectories.
add_subdirectory("source")

if(BUILD_TESTS)
    # Include the test configuration file
    include(cmake/test.cmake)

    enable_testing()
    add_subdirectory("test")
endif()

# Installer les fichiers
install(TARGETS interpreter compiler DESTINATION bin)
install(DIRECTORY include/ DESTINATION include)
