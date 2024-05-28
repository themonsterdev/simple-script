# Include the header directory in the main project
include_directories(PRIVATE "../include")

# Link Google Test libraries
link_libraries(gtest gtest_main context)

# Add test files
add_executable(context_test context_test.cpp)

# Add tests to CTest
add_test(NAME context_test COMMAND context_test)
