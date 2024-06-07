# Add the header files to the library
file(GLOB_RECURSE VALUE_SOURCES "source/*.cpp")

# Create a library for the value
add_library(value ${VALUE_SOURCES})

# Include the header directory in the main project
target_include_directories(value PUBLIC "include")

target_link_libraries(value context)

# Add the test directory
add_subdirectory(test)
