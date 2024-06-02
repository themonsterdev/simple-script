# Exception Handling

Exceptions are a type of error that can be thrown and caught in your code. Use the `throw` keyword to throw an exception and `try-catch` to handle it.

## Throwing Exceptions

```simple_script
function checkAge(age) then
    if age < 18 then
        throw "UnderageError: You must be 18 or older."
    end
    return "Access granted"
end
```

## Handling Exceptions

```simple_script
try then
    var result = checkAge(16)
catch error then
    print(`Error: ${error.message}`)
end
```
