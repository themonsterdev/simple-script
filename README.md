# Simple Script

`Simple Script` is an educational project I created to learn the fundamentals of
programming language development. This project provides an opportunity to explore
and understand key concepts related to the creation and interpretation of scripts.

## Table of Contents

1. Grammar (**EBNF**)
2. Lexical Analysis
3. Syntax Analysis
4. Interpreter

## Grammar (EBNF)

The EBNF (Extended Backus-Naur Form) grammar describes the syntactic structure of the
`Simple Script` language using formal production rules. It defines the different categories
of symbols and the rules for forming expressions and declarations in the language.

```ebnf
Statement
    ::= BlockStatement
    | IfStatement
    | AssignmentStatement
    | ConstDeclarationStatement
    | VarDeclarationStatement
    | DoWhileLoopStatement
    | WhileLoopStatement
    | PrintStatement

BlockStatement
    ::= (Statement)+

IfStatement
    ::= 'if' Expression 'then' BlockStatement ('else' 'if' Expression 'then' BlockStatement)+ ('else' BlockStatement) ? 'end'

AssignmentStatement
    ::= Identifier '=' Expression

ConstDeclarationStatement
    ::= 'const' VariableDeclaration (',' VariableDeclaration)*

VarDeclarationStatement
    ::= 'var' VariableDeclaration (',' VariableDeclaration)*

VariableDeclaration
    ::= Identifier ('=' Expression)?

DoWhileLoopStatement
    ::= 'do' BlockStatement 'while' Expression

WhileLoopStatement
    ::= 'while' Expression 'then' BlockStatement 'end'

PrintStatement
    ::= 'print' '(' Expression ')'

Expression
    ::= TernaryExpression
    | LogicalOrExpression
    | LogicalAndExpression
    | BitwiseOrExpression
    | BitwiseXorExpression
    | BitwiseAndExpression
    | EqualityExpression
    | ComparisonExpression
    | ShiftExpression
    | AdditiveExpression
    | MultiplicativeExpression
    | UnaryExpression

TernaryExpression
    ::= Expression ('?' Expression ':' Expression)*

LogicalOrExpression
    ::= Expression ('||' Expression)*

LogicalAndExpression
    ::= Expression ('&&' Expression)*

BitwiseOrExpression
    ::= Expression ('|' Expression)*

BitwiseXorExpression
    ::= Expression ('^' Expression)*

BitwiseAndExpression
    ::= Expression ('&' Expression)*

EqualityExpression
    ::= Expression (('==' | '!=') Expression)*

ComparisonExpression
    ::= Expression (('<' | '<=' | '>' | '>=' | '<=>') Expression)*

ShiftExpression
    ::= Expression (('<<' | '>>') Expression)*

AdditiveExpression
    ::= Expression (('+' | '-') Expression)*

MultiplicativeExpression
    ::= Expression (('*' | '/' | '%') Expression)*

UnaryExpression
    ::= ('+' | '-' | '!') Expression
    | PrimaryExpression

PrimaryExpression
    ::= Identifier
    | Number
    | String
    | StringFormat
    | Boolean
    | '(' Expression ')'

Identifier
    ::= [a-zA-Z_] [a-zA-Z0-9_]*

Number
    ::= [0-9]+

String
    ::= '"' [^"]* '"'
    | "'" [^']* "'"

StringFormat
    ::= '`' [^"]* '`'

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
    ::= '#' [^\n]*
    ::= '//' [^\n]*

CommentMultiLine
    ::= '/*' ( [^*] | '*'+ [^*/] )* '*'* '*/'
```

For detailed information on the syntax and structure of Simple Script, please refer
to the [Grammar](documentation/grammar/overview.md) documentation.

## Lexical Analysis (Lexer)

Lexical analysis involves converting a string of characters into a sequence of tokens.
In `Simple Script`, the lexer scans the source code to identify and categorize individual
elements such as keywords, identifiers, numbers, and operators.

### Example Output from Lexer

For the code var n = 1 + 2 * 3, the lexer generates the following tokens :

```ts
FToken(Token::KEYWORD,     "var")
FToken(Token::IDENTIFIER,  "n")
FToken(Token::OPERATOR,    "=")
FToken(Token::NUMBER,      "1")
FToken(Token::OPERATOR,    "+")
FToken(Token::NUMBER,      "2")
FToken(Token::OPERATOR,    "*")
FToken(Token::NUMBER,      "3")
FToken(Token::END,         "")
```

## Syntax Analysis (Parser)

Syntax analysis involves validating the grammatical structure of the source code. In `Simple Script`,
the parser uses the tokens produced by the lexer to verify that the code adheres to the language's
syntax. The parser constructs a syntax tree representing the grammatical structure of the code.

### Example AST

For the following code :

```ts
var n = 1 + 2 * 3
print(n)
```

The generated syntax tree would be :

```ts
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

1. Compile the program :

Choose your preferred method :

- If using Visual Studio :
    - Open the solution in Visual Studio.
    - Build the solution using the appropriate build configuration.
- If using CMake Command Line :

```bash
cmake --preset mac-os-debug
cmake --build --preset mac-os-debug
```

2. Run the program :

```bash
build/macos/source/interpreter/interpreter -h
build/macos/source/interpreter/interpreter -f example/test.simplescript
build/macos/source/interpreter/interpreter -t "print(1 + 2 * 3)"
```

The program will read the script.txt file, parse the code, build the syntax tree,
and interpret the instructions.

## Resources

1. [Extended Backus–Naur form](https://en.wikipedia.org/wiki/Extended_Backus–Naur_form)
2. [Lexical analysis](https://en.wikipedia.org/wiki/Lexical_analysis)
3. [Syntax analysis](https://en.wikipedia.org/wiki/Parsing)
4. [Abstract syntax tree](https://en.wikipedia.org/wiki/Abstract_syntax_tree)
5. [Interpreter pattern](https://en.wikipedia.org/wiki/Interpreter_pattern)
6. [Compiler](https://en.wikipedia.org/wiki/Compiler)

## Contribution

Contributions are welcome! If you would like to improve this project, feel free to submit
pull requests or open issues.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more information.
