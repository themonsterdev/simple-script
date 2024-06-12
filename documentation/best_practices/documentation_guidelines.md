# Documentation Guidelines

Good documentation helps others understand your code. Here are some guidelines for writing effective documentation.

## Commenting Code

- Comment your code to explain complex logic.
- Use docstrings for functions and classes.

Example:

```ts
/**
 * Calculates the factorial of a number.
 *
 * @param n The number to calculate the factorial for.
 * @return The factorial of the number.
 */
function factorial(n) then
    if n <= 1 then
        return 1
    end
    return n * factorial(n - 1)
end
```
