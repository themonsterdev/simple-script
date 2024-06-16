# Nom du package .vsix à générer
PACKAGE_NAME=simple-script-monokai

# Chemin vers vsce (assurez-vous que vsce est installé globalement ou dans votre projet)
VSCE=vsce

# Cible par défaut : package
all: package

# Règle pour installer les dépendances (si nécessaire)
install:
	@echo "No dependencies to install."

# Règle pour générer le package .vsix
package: install
	@echo "Packaging extension..."
	$(VSCE) package -o $(PACKAGE_NAME).vsix

# Règle pour nettoyer les fichiers générés
clean:
	@echo "Cleaning up..."
	@rm -f $(PACKAGE_NAME).vsix

# Règle pour publier l'extension (nécessite un token d'authentification)
# Uncomment and configure this rule if you want to enable publishing
# publish:
# 	@echo "Publishing extension..."
# 	$(VSCE) publish

# Afficher de l'aide
help:
	@echo "Makefile for packaging Visual Studio Code extension"
	@echo
	@echo "Usage:"
	@echo "  make          Générer le package .vsix"
	@echo "  make install  Installer les dépendances (si nécessaire)"
	@echo "  make package  Générer le package .vsix"
	@echo "  make clean    Supprimer les fichiers générés"
	@echo "  make help     Afficher cette aide"
