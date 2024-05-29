# Add header files to the library
file(GLOB COMPILER_SOURCES "source/*.cpp")

# Create a library for the compiler
add_executable(compiler ${COMPILER_SOURCES})

# Include the header directory in the main project
target_include_directories(compiler
PUBLIC
	"include"
	"../lexer/include"
	"../parser/include"
)

# Link with libraries
target_link_libraries(compiler lexer parser)
