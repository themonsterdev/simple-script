# Exception Handling

Exceptions are a type of error that can be thrown and caught in your code. Use the `throw` keyword to throw an exception and `try-catch` to handle it.

## Throwing Exceptions

```ts
function checkAge(age) then
    if age < 18 then
        throw "UnderageError: You must be 18 or older."
    end
    return "Access granted"
end
```

## Handling Exceptions

```ts
try
    var result = checkAge(16)
catch error
    print(`Error: ${error}`)
end
```
