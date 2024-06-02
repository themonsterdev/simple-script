# Constants

Constants are immutable values that cannot be changed once they are assigned. They are declared using the `const` keyword.

## Declaring Constants

```our_language
const PI = 3.14;
const GREETING = "Hello, World!";
```

## Usage

Constants can be used in expressions and functions just like variables, but their values cannot be reassigned.

Example:

```our_language
const MAX_USERS = 100;

function getMaxUsers() {
    return MAX_USERS;
}

print("Maximum users allowed: " + getMaxUsers());
```
