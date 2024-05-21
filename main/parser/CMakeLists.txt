# Ajouter les fichiers d'en-tête à la bibliothèque
file(GLOB_RECURSE PARSER_SOURCES "source/*.cpp")

# Créer une bibliothèque pour le parser
add_library(parser ${PARSER_SOURCES})

# Inclure le dossier d'en-tête dans le projet principal
target_include_directories(parser PUBLIC "include")

# Inclure le dossier d'en-tête dans le projet principal
target_include_directories(parser PUBLIC "../lexer/include")

# Lier avec les librairies
target_link_libraries(lexer)

add_subdirectory(test)
