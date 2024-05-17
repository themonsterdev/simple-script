cmake_minimum_required(VERSION 3.10)
project(simple-script)

# Déclaration des fichiers sources
set(SOURCES
    src/main.cpp
    
    src/interpreter.hpp
    src/interpreter.cpp

    src/expressions.hpp
    src/expressions.cpp

    src/statements.hpp
    src/statements.cpp
    # Ajoutez ici tous vos fichiers source
)

# Configuration des exécutables
add_executable(simple-script ${SOURCES})

# Configuration spécifique à Windows (Visual Studio)
if(WIN32)
    # Options de compilation pour Visual Studio
    target_compile_options(simple-script PRIVATE /W3 /WX)
endif()

# Configuration spécifique à macOS
if(APPLE)
    # Options de compilation pour macOS (Clang)
    target_compile_options(simple-script PRIVATE -Wall -Wextra -Werror)
endif()
