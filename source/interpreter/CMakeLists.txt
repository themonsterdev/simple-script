# Add header files to the library
file(GLOB_RECURSE AST_SOURCES "${PROJECT_SOURCE_DIR}/source/ast/*.cpp")
file(GLOB_RECURSE CONTEXT_SOURCES "${PROJECT_SOURCE_DIR}/source/context/*.cpp")
file(GLOB_RECURSE INTERPRETER_SOURCES "${PROJECT_SOURCE_DIR}/source/interpreter/*.cpp")
file(GLOB_RECURSE PARSER_SOURCES "${PROJECT_SOURCE_DIR}/source/parser/*.cpp")
file(GLOB_RECURSE SCOPE_SOURCES "${PROJECT_SOURCE_DIR}/source/scope/*.cpp")
file(GLOB_RECURSE TYPE_SOURCES "${PROJECT_SOURCE_DIR}/source/type/*.cpp")
file(GLOB_RECURSE VALUE_SOURCES "${PROJECT_SOURCE_DIR}/source/value/*.cpp")

set(FILE_SOURCES 
    ${AST_SOURCES}
    ${CONTEXT_SOURCES}
    ${INTERPRETER_SOURCES}
    ${PARSER_SOURCES}
    ${SCOPE_SOURCES}
    ${TYPE_SOURCES}
    ${VALUE_SOURCES}
)

# Create an executable for the interpreter
add_executable(interpreter ${FILE_SOURCES})

# Include the header directory in the project
target_include_directories(interpreter PUBLIC "${PROJECT_SOURCE_DIR}/include")

target_link_libraries(interpreter lexer)

# Définir les propriétés de l'exécutable
set_target_properties(interpreter PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
)
