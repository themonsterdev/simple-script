# Include the header directory in the main project
include_directories(PRIVATE "../include")

# Link Google Test libraries
link_libraries(gtest gtest_main value)

# Add test files
add_executable(value_test value_test.cpp)

# Add tests to CTest
add_test(NAME value_test COMMAND value_test)
