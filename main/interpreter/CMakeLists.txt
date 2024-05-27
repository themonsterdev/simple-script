# Add header files to the library
file(GLOB INTERPRETER_SOURCES "source/*.cpp")

# Create an executable for the interpreter
add_executable(interpreter ${INTERPRETER_SOURCES})

# Include the header directory in the main project
target_include_directories(interpreter
PUBLIC
	"include"
	"../lexer/include"
	"../parser/include"
)

# Link with the libraries
target_link_libraries(interpreter lexer parser)
