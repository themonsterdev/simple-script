# Modules and Packages

Modules and packages help you organize your code into reusable components. Use the `import` and `export` keywords to work with modules.

## Creating a Module

```ts
// math.simple_script
export function add(a, b) then
    return a + b
end

export function subtract(a, b) then
    return a - b
end
```

## Importing a Module

```ts
import { add, subtract } from 'math'

var sum = add(5, 3)
var difference = subtract(5, 3)

print("Sum: " + sum)               // Outputs: Sum: 8
print(`Difference: ${difference}`) // Outputs: Difference: 2
```
