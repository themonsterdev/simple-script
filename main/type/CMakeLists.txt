# Add the header files to the library
file(GLOB_RECURSE TYPE_SOURCES "source/*.cpp")

# Create a library for the type
add_library(type ${TYPE_SOURCES})

# Include the header directory in the main project
target_include_directories(type PUBLIC "include")

target_link_libraries(type value)

# Add the test directory
# add_subdirectory(test)
