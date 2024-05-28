# Simple Script

`Simple Script` is an educational project I created to learn the fundamentals of
programming language development. This project provides an opportunity to explore
and understand key concepts related to the creation and interpretation of scripts.

## Table of Contents

1. Grammar (EBNF)
2. Lexical Analysis (Lexer)
3. Syntax Analysis (Parser)
4. Interpretation or Code Generation

## Grammar (EBNF)

The EBNF (Extended Backus-Naur Form) grammar describes the syntactic structure of the
`Simple Script` language using formal production rules. It defines the different categories
of symbols and the rules for forming expressions and declarations in the language.

```ebnf
Statement
    ::= VarDeclarationStatement
    | AssignmentStatement
    | PrintStatement

VarDeclarationStatement
    ::= 'var' VarDeclaration (',' VarDeclaration)*

VarDeclaration
    ::= Identifier ('=' ExpressionList)?

AssignmentStatement
    ::= Identifier '=' ExpressionList

PrintStatement
    ::= 'print' ExpressionList

ExpressionList
    ::= Identifier
    | Number
    | String
    | Boolean
    | ArithmeticOperatorExpression
    | ComparisonOperatorExpression
    | StringOperatorExpression

ArithmeticOperatorExpression
    ::= ( Number | Identifier ) ( '*' | '+' | '-' | '/' | '%' ) ( Number | Identifier )

ComparisonOperatorExpression
    ::= ( String | Number | Boolean | Identifier ) ( '==' | '>' | '>=' | '<' | '<=' | '!=' ) ( String | Number | Boolean | Identifier )

StringOperatorExpression
    ::= ( String | Identifier ) ( '+' | '*' ) ( String | Identifier )

Identifier
    ::= [a-zA-Z_] [a-zA-Z0-9_]*

Number
    ::= [0-9]+

String
    ::= '"' [^"]* '"'
    | "'" [^']* "'"

Boolean
    ::= 'false'
    | 'true'

Whitespace
    ::= Space
    | Comment

Space
    ::= '\t'
    | '\n'
    | '\r'
    | ' '

Comment
    ::= CommentSingleLine
    | CommentMultiLine

CommentSingleLine
    ::= '//' [^\n]*

CommentMultiLine
    ::= '/*' ( [^*] | '*'+ [^*/] )* '*'* '*/'
```

For detailed information on the syntax and structure of Simple Script, please refer
to the [Grammar](documentation/grammar/index.md) documentation.

## Lexical Analysis (Lexer)

Lexical analysis involves converting a string of characters into a sequence of tokens.
In `Simple Script`, the lexer scans the source code to identify and categorize individual
elements such as keywords, identifiers, numbers, and operators.

### Example Output from Lexer

For the code var n = 1 + 2 * 3, the lexer generates the following tokens :

```
SToken(Token::KEYWORD,     "var")
SToken(Token::IDENTIFIER,  "n")
SToken(Token::OPERATOR,    "=")
SToken(Token::NUMBER,      "1")
SToken(Token::OPERATOR,    "+")
SToken(Token::NUMBER,      "2")
SToken(Token::OPERATOR,    "*")
SToken(Token::NUMBER,      "3")
SToken(Token::END,         "")
```

## Syntax Analysis (Parser)

Syntax analysis involves validating the grammatical structure of the source code. In `Simple Script`,
the parser uses the tokens produced by the lexer to verify that the code adheres to the language's
syntax. The parser constructs a syntax tree representing the grammatical structure of the code.

### Example AST

For the following code :

```
var n = 1 + 2 * 3
print n
```

The generated syntax tree would be :

```
     root
    /    \ 
 var     print
 / \       |
n   +      n
   / \
  1   *
     / \
    2   3
```

## Interpretation or Code Generation

### Interpretation

After constructing the syntax tree, the interpreter traverses the instructions
represented by each node. This approach allows `Simple Script` code to be executed
directly without the need for prior compilation.

### Code Generation

Code generation is the next step to be implemented. This process will involve translating
`Simple Script` code into machine code or an intermediate language, which can then be compiled
and executed. Future steps will include creating source files, compiling them, and executing
the resulting code.

## Usage

To run a script with `Simple Script`, follow these steps :

1. Create a script file, for example, script.txt, with the following content :

```c
print "Hello, world"
```

2. Compile the program :

Choose your preferred method :

- If using Visual Studio :
    - Open the solution in Visual Studio.
    - Build the solution using the appropriate build configuration.
- If using CMake :

```bash
mkdir build
cd build
cmake ..
make
```

3. Run the program :

```bash
cd out\build\x64-Debug\main\interpreter
or
cd build\main\interpreter\Debug
.\interpreter.exe -f ../../../../../examples/test.txt
```

The program will read the script.txt file, parse the code, build the syntax tree,
and interpret the instructions.

## Contribution

Contributions are welcome! If you would like to improve this project, feel free to submit
pull requests or open issues.

## License

This project is licensed under the MIT License. See the `LICENSE` file for more information.
