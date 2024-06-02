# Syntax Rules

Simple Script has a set of rules that define its syntax. Here are some of the most important ones:

## Variables

- Variables must be declared before use.
- Use the `var` keyword to declare a variable.

Example:

```simple_script
var x = 10
var name = "Alice"
```

## Functions

- Functions are defined using the `function` keyword.
- Parameters are enclosed in parentheses `()` and the body is enclosed between `then` and `end`.

Example:

```simple_script
function greet(name)
then
    print(`Hello, ${name}`)
end
```

## Control Structures

- Use `if`, `else if`, and `else` for conditional statements.
- Loops can be created using `for`, `while`, and `do while`.

Example:

```simple_script
if x > 0 then
    print("Positive")
else
    print("Non-positive")
end
```
