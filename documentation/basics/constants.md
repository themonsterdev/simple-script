# Constants

Constants are immutable values that cannot be changed once they are assigned. They are declared using the `const` keyword.

## Declaring Constants

```simple_script
const PI = 3.14
const GREETING = "Hello, World!"
```

## Usage

Constants can be used in expressions and functions just like variables, but their values cannot be reassigned.

Example:

```simple_script
const MAX_USERS = 100

function getMaxUsers() then
    return MAX_USERS
end

const maxUsers = getMaxUsers()
print(`Maximum users allowed: ${maxUsers}`)
```
