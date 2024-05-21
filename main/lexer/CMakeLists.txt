# Configuration de la bibliothèque d'en-têtes lexer

# Ajouter les fichiers d'en-tête à la bibliothèque
file(GLOB LEXER_HEADERS "include/*.hpp")
file(GLOB LEXER_SOURCES "source/*.cpp")

# Créer une bibliothèque pour le lexer
add_library(lexer ${LEXER_SOURCES} ${LEXER_HEADERS})

# Inclure le dossier d'en-tête dans le projet principal
target_include_directories(lexer PUBLIC include)

add_subdirectory(test)
