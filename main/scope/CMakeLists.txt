# Add the header files to the library
file(GLOB SCOPE_SOURCES "source/*.cpp")

# Create a library for the scope
add_library(scope ${SCOPE_SOURCES})

# Include the header directory in the main project
target_include_directories(scope PUBLIC "include")

target_link_libraries(scope ast)

# Add the test directory
add_subdirectory(test)
