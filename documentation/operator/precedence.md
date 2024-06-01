# Operator Precedence

The `Simple Script` language follows standard operator precedence
rules for evaluating expressions.

| Precedence | Operator         | Description                                               | Associativity   |
|------------|------------------|-----------------------------------------------------------|-----------------|
| 1          | a++, a--         | Suffix/postfix increment and decrement                    | Left-to-right → |
| 2          | ++a, --a         | Prefix increment and decrement                            | Right-to-left ← |
|            | +a, -a           | Unary plus and minus                                      |                 |
|            | !, ~             | Logical and bitwise NOT                                   |                 |
|            | *a               | Indirection (dereference)                                 |                 |
|            | &a               | Address-of                                                |                 |
| 3          | a*b, a/b, a%b    | Multiplication, division, remainder                       |                 |
| 4          | a+b, a-b         | Addition, subtraction                                     |                 |
| 5          | <<, >>           | Bitwise left shift and right shift                        |                 |
| 6          | <=>              | Three-way comparison operator                             |                 |
| 7          | <, <=, >, >=     | Relational operators                                      |                 |
| 8          | ==, !=           | Equality operators                                        |                 |
| 9          | a&b              | Bitwise AND                                               |                 |
| 10         | ^                | Bitwise XOR (exclusive or)                                |                 |
| 11         | |                | Bitwise OR (inclusive or)                                 |                 |
| 12         | &&               | Logical AND                                               |                 |
| 13         | ||               | Logical OR                                                |                 |
| 14         | a?b:c            | Ternary conditional                                       | Right-to-left ← |
|            | =                | Direct assignment                                         |                 |
|            | +=, -=           | Compound assignment by sum, difference                    |                 |
|            | *=, /=, %=       | Compound assignment by product, quotient, and remainder   |                 |
|            | <<=, >>=         | Compound assignment by bitwise left shift and right shift |                 |
|            | &=, ^=, \|=      | Compound assignment by bitwise AND, XOR, and OR           |                 |
| 15         | ,                | Comma                                                     | Left-to-right → |
