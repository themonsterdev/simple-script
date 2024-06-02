# Exception Handling

Exceptions are a type of error that can be thrown and caught in your code. Use the `throw` keyword to throw an exception and `try-catch` to handle it.

## Throwing Exceptions

```our_language
function checkAge(age) {
    if (age < 18) {
        throw "UnderageError: You must be 18 or older.";
    }
    return "Access granted";
}
```

## Handling Exceptions

```our_language
try {
    var result = checkAge(16);
} catch (error) {
    print("Error: " + error);
}
```
