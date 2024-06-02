# Return Values

Functions can return values using the `return` statement. This value can be used where the function is called.

## Returning a Value

```our_language
function add(a, b) {
    return a + b;
}

var result = add(5, 3);
print(result); // Outputs: 8
```

## Returning No Value

If no return statement is used, the function returns undefined.

```our_language
function sayHello() {
    print("Hello, World!");
}

var result = sayHello(); // Outputs: Hello, World!
print(result);           // Outputs: undefined
```
