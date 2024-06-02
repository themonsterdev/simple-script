# Documentation Guidelines

Good documentation helps others understand your code. Here are some guidelines for writing effective documentation.

## Commenting Code

- Comment your code to explain complex logic.
- Use docstrings for functions and classes.

Example:

```our_language
/**
 * Calculates the factorial of a number.
 *
 * @param n The number to calculate the factorial for.
 * @return The factorial of the number.
 */
function factorial(n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}
```

## Writing Readme Files

Include a Readme file in your project with an overview, installation instructions, usage examples, and license information.

Example:

```md
# Project Name

## Overview

This project does X, Y, and Z.

## Installation

1. Step one
2. Step two

## Usage

\`\`\`our_language
var example = new Example();
example.run();
\`\`\`

## License

This project is licensed under the MIT License.
```
