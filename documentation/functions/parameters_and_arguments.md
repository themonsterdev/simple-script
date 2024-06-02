# Parameters and Arguments

Functions can accept parameters, which are variables that you pass into the function. These parameters can be used within the function.

## Defining Parameters

```our_language
function greet(name) {
    print("Hello, " + name);
}
```

## Passing Arguments

```our_language
greet("Alice"); // Outputs: Hello, Alice
```

## Multiple Parameters

```our_language
function add(a, b) {
    return a + b;
}

var result = add(5, 3);
print(result); // Outputs: 8
```
