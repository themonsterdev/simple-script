# Link Google Test libraries
link_libraries(gtest gtest_main ast context)

# Include the header directory
include_directories(PUBLIC "../include")

add_subdirectory(expression)
add_subdirectory(statement)
