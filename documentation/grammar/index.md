## Grammar (EBNF)

The EBNF (Extended Backus-Naur Form) grammar describes the syntactic structure of the
`Simple Script` language using formal production rules. It defines the different categories
of symbols and the rules for forming expressions and declarations in the language.

**Statement:**

![Statement](diagram/Statement.svg)

```
Statement
         ::= BlockStatement
           | IfStatement
           | AssignmentStatement
           | ConstDeclarationStatement
           | VarDeclarationStatement
           | DoWhileLoopStatement
           | WhileLoopStatement
           | PrintStatement
```

referenced by:

* BlockStatement

**BlockStatement:**

![BlockStatement](diagram/BlockStatement.svg)

```
BlockStatement
         ::= Statement+
```

referenced by:

* DoWhileLoopStatement
* IfStatement
* Statement
* WhileLoopStatement

**IfStatement:**

![IfStatement](diagram/IfStatement.svg)

```
IfStatement
         ::= 'if' Expression 'then' BlockStatement ( 'else' 'if' Expression 'then' BlockStatement )+ ( 'else' BlockStatement )? 'end'
```

referenced by:

* Statement

**AssignmentStatement:**

![AssignmentStatement](diagram/AssignmentStatement.svg)

```
AssignmentStatement
         ::= Identifier '=' Expression
```

referenced by:

* Statement

**ConstDeclarationStatement:**

![ConstDeclarationStatement](diagram/ConstDeclarationStatement.svg)

```
ConstDeclarationStatement
         ::= 'const' VariableDeclaration ( ',' VariableDeclaration )*
```

referenced by:

* Statement

**VarDeclarationStatement:**

![VarDeclarationStatement](diagram/VarDeclarationStatement.svg)

```
VarDeclarationStatement
         ::= 'var' VariableDeclaration ( ',' VariableDeclaration )*
```

referenced by:

* Statement

**VariableDeclaration:**

![VariableDeclaration](diagram/VariableDeclaration.svg)

```
VariableDeclaration
         ::= Identifier ( '=' Expression )?
```

referenced by:

* ConstDeclarationStatement
* VarDeclarationStatement

**DoWhileLoopStatement:**

![DoWhileLoopStatement](diagram/DoWhileLoopStatement.svg)

```
DoWhileLoopStatement
         ::= 'do' BlockStatement 'while' Expression
```

referenced by:

* Statement

**WhileLoopStatement:**

![WhileLoopStatement](diagram/WhileLoopStatement.svg)

```
WhileLoopStatement
         ::= 'while' Expression 'then' BlockStatement 'end'
```

referenced by:

* Statement

**PrintStatement:**

![PrintStatement](diagram/PrintStatement.svg)

```
PrintStatement
         ::= 'print' '(' Expression ')'
```

referenced by:

* Statement

**Expression:**

![Expression](diagram/Expression.svg)

```
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
```

referenced by:

* AdditiveExpression
* AssignmentStatement
* BitwiseAndExpression
* BitwiseOrExpression
* BitwiseXorExpression
* ComparisonExpression
* DoWhileLoopStatement
* EqualityExpression
* IfStatement
* LogicalAndExpression
* LogicalOrExpression
* MultiplicativeExpression
* PrimaryExpression
* PrintStatement
* ShiftExpression
* TernaryExpression
* UnaryExpression
* VariableDeclaration
* WhileLoopStatement

**TernaryExpression:**

![TernaryExpression](diagram/TernaryExpression.svg)

```
TernaryExpression
         ::= Expression ( '?' Expression ':' Expression )*
```

referenced by:

* Expression

**LogicalOrExpression:**

![LogicalOrExpression](diagram/LogicalOrExpression.svg)

```
LogicalOrExpression
         ::= Expression ( '||' Expression )*
```

referenced by:

* Expression

**LogicalAndExpression:**

![LogicalAndExpression](diagram/LogicalAndExpression.svg)

```
LogicalAndExpression
         ::= Expression ( '&&' Expression )*
```

referenced by:

* Expression

**BitwiseOrExpression:**

![BitwiseOrExpression](diagram/BitwiseOrExpression.svg)

```
BitwiseOrExpression
         ::= Expression ( '|' Expression )*
```

referenced by:

* Expression

**BitwiseXorExpression:**

![BitwiseXorExpression](diagram/BitwiseXorExpression.svg)

```
BitwiseXorExpression
         ::= Expression ( '^' Expression )*
```

referenced by:

* Expression

**BitwiseAndExpression:**

![BitwiseAndExpression](diagram/BitwiseAndExpression.svg)

```
BitwiseAndExpression
         ::= Expression ( '&' Expression )*
```

referenced by:

* Expression

**EqualityExpression:**

![EqualityExpression](diagram/EqualityExpression.svg)

```
EqualityExpression
         ::= Expression ( ( '==' | '!=' ) Expression )*
```

referenced by:

* Expression

**ComparisonExpression:**

![ComparisonExpression](diagram/ComparisonExpression.svg)

```
ComparisonExpression
         ::= Expression ( ( '<' | '<=' | '>' | '>=' | '<=>' ) Expression )*
```

referenced by:

* Expression

**ShiftExpression:**

![ShiftExpression](diagram/ShiftExpression.svg)

```
ShiftExpression
         ::= Expression ( ( '<<' | '>>' ) Expression )*
```

referenced by:

* Expression

**AdditiveExpression:**

![AdditiveExpression](diagram/AdditiveExpression.svg)

```
AdditiveExpression
         ::= Expression ( ( '+' | '-' ) Expression )*
```

referenced by:

* Expression

**MultiplicativeExpression:**

![MultiplicativeExpression](diagram/MultiplicativeExpression.svg)

```
MultiplicativeExpression
         ::= Expression ( ( '*' | '/' | '%' ) Expression )*
```

referenced by:

* Expression

**UnaryExpression:**

![UnaryExpression](diagram/UnaryExpression.svg)

```
UnaryExpression
         ::= ( '+' | '-' | '!' ) Expression
           | PrimaryExpression
```

referenced by:

* Expression

**PrimaryExpression:**

![PrimaryExpression](diagram/PrimaryExpression.svg)

```
PrimaryExpression
         ::= Identifier
           | Number
           | String
           | StringFormat
           | Boolean
           | '(' Expression ')'
```

referenced by:

* UnaryExpression

**Identifier:**

![Identifier](diagram/Identifier.svg)

```
Identifier
         ::= [a-zA-Z_] [a-zA-Z0-9_]*
```

referenced by:

* AssignmentStatement
* PrimaryExpression
* VariableDeclaration

**Number:**

![Number](diagram/Number.svg)

```
Number   ::= [0-9]+
```

referenced by:

* PrimaryExpression

**String:**

![String](diagram/String.svg)

```
String   ::= '"' [^"]* '"'
           | "'" [^']* "'"
```

referenced by:

* PrimaryExpression

**StringFormat:**

![StringFormat](diagram/StringFormat.svg)

```
StringFormat
         ::= '`' [^"]* '`'
```

referenced by:

* PrimaryExpression

**Boolean:**

![Boolean](diagram/Boolean.svg)

```
Boolean  ::= 'false'
           | 'true'
```

referenced by:

* PrimaryExpression

**Whitespace:**

![Whitespace](diagram/Whitespace.svg)

```
Whitespace
         ::= Space
           | Comment
```

**Space:**

![Space](diagram/Space.svg)

```
Space    ::= '\t'
           | '\n'
           | '\r'
           | ' '
```

referenced by:

* Whitespace

**Comment:**

![Comment](diagram/Comment.svg)

```
Comment  ::= CommentSingleLine
           | CommentMultiLine
```

referenced by:

* Whitespace

**CommentSingleLine:**

![CommentSingleLine](diagram/CommentSingleLine.svg)

```
CommentSingleLine
         ::= '//' [^\n]*
```

referenced by:

* Comment

![CommentMultiLine](diagram/CommentMultiLine.svg)

```
CommentMultiLine
    ::= '/*' ( [^*] | '*'+ [^*/] )* '*'* '*/'
```

referenced by:

* Comment

<sup>generated by [RR - Railroad Diagram Generator][RR]</sup>

[RR]: https://rr.red-dove.com/ui
