# Include the header directory in the main project
include_directories(PRIVATE "../include")

# Link Google Test libraries
link_libraries(gtest gtest_main scope)

# Add test files
add_executable(scope_test scope_test.cpp)

# Add tests to CTest
add_test(NAME scope_test COMMAND scope_test)
