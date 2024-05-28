# Add the header files to the library
file(GLOB_RECURSE PARSER_SOURCES "source/*.cpp")

# Create a library for the parser
add_library(parser ${PARSER_SOURCES})

# Include the header directory in the main project
target_include_directories(parser
PUBLIC
	"include"
	"../ast/include"
)

# Include the lexer header directory in the main project
target_include_directories(parser PUBLIC "../lexer/include")

# Link with the lexer library
target_link_libraries(parser lexer ast)

# Add the test directory
add_subdirectory(test)
