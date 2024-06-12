# Return Values

Functions can return values using the `return` statement. This value can be used where the function is called.

## Returning a Value

```ts
function add(a, b) then
    return a + b
end

var result = add(5, 3)
print(result) // Outputs: 8
```

## Returning No Value

If no return statement is used, the function returns undefined.

```ts
function sayHello() then
    print("Hello, World!")
end

var result = sayHello() // Outputs: Hello, World!
print(result)           // Outputs: undefined
```
