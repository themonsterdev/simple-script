# Add the header files to the library
file(GLOB_RECURSE AST_SOURCES "source/*.cpp")

# Create a library for the AST
add_library(ast ${AST_SOURCES})

# Set the include directories for the library
target_include_directories(ast PUBLIC "include")

# Link the AST library with the context library
target_link_libraries(ast context)

# Add the test directory
add_subdirectory(test)
