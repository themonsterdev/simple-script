# Déclaration des fichiers sources pour les tests
file(GLOB TEST_SOURCES "*.cpp")

# Configuration de l'exécutable de test
add_executable(lexer_test ${TEST_SOURCES})

# Inclure le dossier d'en-tête dans le projet principal
target_include_directories(lexer_test PUBLIC ../include)

# Lier avec les librairies
target_link_libraries(lexer_test gtest gtest_main lexer)

# Ajouter le test à CTest
add_test(NAME TokenizerTest COMMAND tokenizer_test)
