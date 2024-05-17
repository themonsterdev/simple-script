# Simple Script

## Grammaire EBNF

```ebnf
Statement
    ::= ( print | Identifier '=' ) ExpressionList
    | var Identifier ( '=' ExpressionList )

ExpressionList
    ::= Identifier
    | ArithmeticOperatorExpression
    | ComparisonOperatorExpression

ArithmeticOperatorExpression
    ::= ( Number | Identifier ) ( '*' | '+' | '-' | '/' | '=' | '%' ) ( Number | Identifier )

ComparisonOperatorExpression
    ::= ( Number | Identifier ) ( '==' | '>' | '>=' | '<' | '<=' | '!=' ) ( Number | Identifier )

Identifier
    ::= [a-zA-Z_] [a-zA-Z0-9_]+

Number
    ::= [0-9]+
```
