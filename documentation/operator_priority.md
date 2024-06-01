# Operator Precedence in the Simple Script Language

The `Simple Script` language follows standard operator precedence
rules for evaluating expressions.

| Precedence | Operator         | Description                                               | Associativity |
|------------|------------------|-----------------------------------------------------------|---------------|
| 1          | ::               | Scope resolution                                          | Left-to-right |
| 2          | a++, a--         | Suffix/postfix increment and decrement                    |               |
|            | type(), type{}   | Functional cast                                           |               |
|            | a(), a[]         | Function call and subscript                               |               |
|            | ., ->            | Member access                                             |               |
| 3          | ++a, --a         | Prefix increment and decrement                            | Right-to-left |
|            | +a, -a           | Unary plus and minus                                      |               |
|            | !, ~             | Logical and bitwise NOT                                   |               |
|            | (type)           | C-style cast                                              |               |
|            | *a               | Indirection (dereference)                                 |               |
|            | &a               | Address-of                                                |               |
|            | sizeof           | Size-of                                                   |               |
|            | co_await         | await-expression (C++20)                                  |               |
|            | new, new[]       | Dynamic memory allocation                                 |               |
|            | delete, delete[] | Dynamic memory deallocation                               |               |
| 4          | .*, ->*          | Pointer-to-member                                         | Left-to-right |
| 5          | *, /, %          | Multiplication, division, remainder                       |               |
| 6          | +, -             | Addition, subtraction                                     |               |
| 7          | <<, >>           | Bitwise left shift and right shift                        |               |
| 8          | <=>              | Three-way comparison operator (C++20)                     |               |
| 9          | <, <=, >, >=     | Relational operators                                      |               |
| 10         | ==, !=           | Equality operators                                        |               |
| 11         | &                | Bitwise AND                                               |               |
| 12         | ^                | Bitwise XOR (exclusive or)                                |               |
| 13         | \|               | Bitwise OR (inclusive or)                                 |               |
| 14         | &&               | Logical AND                                               |               |
| 15         | \|\|             | Logical OR                                                |               |
| 16         | ?:               | Ternary conditional                                       | Right-to-left |
|            | throw            | Throw operator                                            |               |
|            | co_yield         | Yield-expression (C++20)                                  |               |
|            | =                | Direct assignment                                         |               |
|            | +=, -=           | Compound assignment by sum, difference                    |               |
|            | *=, /=, %=       | Compound assignment by product, quotient, and remainder   |               |
|            | <<=, >>=         | Compound assignment by bitwise left shift and right shift |               |
|            | &=, ^=, \|=      | Compound assignment by bitwise AND, XOR, and OR           |               |
| 17         | ,                | Comma                                                     | Left-to-right |


1. Multiplication, Division, Modulo (`*`, `/`, `%`)
2. Addition, Subtraction (`+`, `-`)
3. Comparison (`==`, `!=`, `<`, `<=`, `>`, `>=`)
4. Logical `&&`, `||`, `!`
5. Bitwise `&`, `|`, `^`
6. Shift `<<`, `>>`
7. Ternary `? :`
8. Unary `+`, `-`, `!`
9. Primary (parentheses, numbers, booleans, strings, identifiers)
