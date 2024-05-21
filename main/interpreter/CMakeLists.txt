# Ajouter les fichiers d'en-tête à la bibliothèque
file(GLOB INTERPRETER_SOURCES "source/*.cpp")

# Créer une bibliothèque pour le interpreter
add_executable(interpreter ${INTERPRETER_SOURCES})

# Inclure le dossier d'en-tête dans le projet principal
target_include_directories(interpreter
PUBLIC
	include
	"../lexer/include"
	"../parser/include"
)

# Lier avec les librairies
target_link_libraries(interpreter lexer parser)
