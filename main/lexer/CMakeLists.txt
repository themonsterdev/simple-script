# Configuration of the lexer header library

# Add header files to the library
file(GLOB LEXER_SOURCES "source/*.cpp")

# Create a library for the lexer
add_library(lexer ${LEXER_SOURCES})

# Include the header directory in the main project
target_include_directories(lexer PUBLIC include)

# Add the test subdirectory
add_subdirectory(test)
