# Déclaration des fichiers sources pour les tests
file(GLOB TEST_SOURCES "*.cpp")

# Configuration de l'exécutable de test
add_executable(parser_test ${TEST_SOURCES})

# Inclure le dossier d'en-tête dans le projet principal
target_include_directories(parser_test PUBLIC "../include")

# Lier avec les librairies
target_link_libraries(parser_test gtest gtest_main lexer parser)

# Ajouter le test à CTest
add_test(NAME ParserTest COMMAND ParserTest)
