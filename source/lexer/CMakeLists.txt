# Add header files to the library
file(GLOB_RECURSE LEXER_SOURCES "${PROJECT_SOURCE_DIR}/source/lexer/*.cpp")

# Create an executable for the lexer
add_library(lexer ${LEXER_SOURCES})

# Include the header directory in the project
target_include_directories(lexer PUBLIC "${PROJECT_SOURCE_DIR}/include")

# Définir les propriétés de l'exécutable
set_target_properties(lexer PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
)
