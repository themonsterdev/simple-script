cmake_minimum_required(VERSION 3.10)
project(simple-script)

# Télécharger et inclure Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)
FetchContent_MakeAvailable(googletest)

# Inclure les sous-dossiers du projet
add_subdirectory(main)
