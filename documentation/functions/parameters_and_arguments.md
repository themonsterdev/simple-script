# Parameters and Arguments

Functions can accept parameters, which are variables that you pass into the function. These parameters can be used within the function.

## Defining Parameters

```simple_script
function greet(name) then
    print(`Hello, ${name}`)
end
```

## Passing Arguments

```simple_script
greet("Alice") // Outputs: Hello, Alice
```

## Multiple Parameters

```simple_script
function add(a, b) then
    return a + b
end

var result = add(5, 3)
print(result) // Outputs: 8
```
