# Parameters and Arguments

Functions can accept parameters, which are variables that you pass into the function. These parameters can be used within the function.

## Defining Parameters

```ts
function greet(name) then
    print(`Hello, ${name}`)
end
```

## Passing Arguments

```ts
greet("Alice") // Outputs: Hello, Alice
```

## Multiple Parameters

```ts
function add(a, b) then
    return a + b
end

var result = add(5, 3)
print(result) // Outputs: 8
```
