# Add the header files to the library
file(GLOB_RECURSE CONTEXT_SOURCES "source/*.cpp")

# Create a library for the context
add_library(context ${CONTEXT_SOURCES})

# Include the header directory in the main project
target_include_directories(context PUBLIC "include")

# Link with libraries
target_link_libraries(context scope ast)

# Add the test directory
add_subdirectory(test)
