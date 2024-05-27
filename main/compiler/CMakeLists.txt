# Ajouter les fichiers d'en-tête à la bibliothèque
file(GLOB COMPILER_SOURCES "source/*.cpp")

# Créer une bibliothèque pour le compiler
add_executable(compiler ${COMPILER_SOURCES})

# Inclure le dossier d'en-tête dans le projet principal
target_include_directories(compiler
PUBLIC
	include
	"../lexer/include"
	"../parser/include"
)

# Lier avec les librairies
target_link_libraries(compiler lexer parser)
