# Add the header files to the library
file(GLOB CONTEXT_SOURCES "source/*.cpp")

# Create a library for the context
add_library(context ${CONTEXT_SOURCES})

# Include the header directory in the main project
target_include_directories(context PUBLIC "include")

target_link_libraries(context scope)

# Add the test directory
add_subdirectory(test)
