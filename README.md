# Simple Script

`Simple Script` est un projet éducatif que j'ai créé dans le but d'apprendre les
fondamentaux du développement de langages de programmation. Ce projet offre une
opportunité d'explorer et de comprendre les concepts clés liés à la création et
à l'interprétation de scripts.

## Table des matières

1. Grammaire (EBNF)
2. Analyse lexicale (Lexer)
3. Analyse syntaxique (Parser)
4. Interprétation ou génération de code

## Grammaire (EBNF)

La grammaire EBNF (Extended Backus-Naur Form) décrit la structure syntaxique du langage
`Simple Script` à l'aide de règles de production formelles. Elle définit les différentes
catégories de symboles et les règles de formation des expressions et des déclarations
dans le langage.

```ebnf
Statement
    ::= ( print | Identifier '=' ) ExpressionList
    | var Identifier ( '=' ExpressionList )

ExpressionList
    ::= Identifier
    | ArithmeticOperatorExpression
    | ComparisonOperatorExpression

ArithmeticOperatorExpression
    ::= ( Number | Identifier ) ( '*' | '+' | '-' | '/' | '%' ) ( Number | Identifier )

ComparisonOperatorExpression
    ::= ( Number | Identifier ) ( '==' | '>' | '>=' | '<' | '<=' | '!=' ) ( Number | Identifier )

Identifier
    ::= [a-zA-Z_] [a-zA-Z0-9_]+

Number
    ::= [0-9]+
```

## Analyse lexicale (Lexer)

L'analyse lexicale consiste à convertir une chaîne de caractères en une séquence de
jetons (tokens). Dans le cadre de `Simple Script`, le lexer analyse le code source pour
identifier et catégoriser les éléments individuels, tels que les mots-clés, les
identifiants, les nombres et les opérateurs.

> Remarque: Continuez à développer cette classe pour gérer tous les types de jetons
définis dans la grammaire du langage `Simple Script`.

## Analyse syntaxique (Parser)

L'analyse syntaxique implique la validation de la structure grammaticale du code source.
Dans `Simple Script`, le parser utilise les jetons produits par le lexer pour vérifier
que le code respecte la syntaxe du langage. Le parser construit un arbre syntaxique qui
représente la structure grammaticale du code.

### Exemple d'AST

Pour le code suivant :

```
var n = 0
print n
```

L'arbre syntaxique généré serait :

```
  =   print
 / \    |
n   0   n
```

## Interprétation ou génération de code

### Interprétation

Après avoir construit l'arbre syntaxique, l'interpréteur parcourt les instructions représentées
par chaque nœud. Cette approche permet d'exécuter directement le code `Simple Script` sans
nécessiter de compilation préalable.

### Génération de code

La génération de code est la prochaine étape à implémenter. Ce processus consistera à traduire le code
`Simple Script` en code machine ou dans un langage intermédiaire, qui pourra ensuite être compilé et exécuté.
Les étapes futures incluront la création de fichiers source, leur compilation et l'exécution du
code résultant.

## Utilisation

Pour exécuter un script avec `Simple Script`, suivez ces étapes :

1. Créez un fichier de script, par exemple script.txt, avec le contenu suivant :

```c
var n = 1 + 2 * 3
print n

var i = 2
var j = 1 + i
print j
```

2. Compilez et exécutez le programme :

```bash
mkdir build
cd build
cmake ..
make
./votre_executable script.txt
```

Le programme lira le fichier script.txt, analysera le code, construira l'arbre syntaxique et
interprétera les instructions.

## Contribution

Les contributions sont les bienvenues ! Si vous souhaitez améliorer ce projet, n'hésitez pas à soumettre
des pull requests ou à ouvrir des issues.

## Licence

Ce projet est sous licence MIT. Voir le fichier `LICENSE` pour plus d'informations.
