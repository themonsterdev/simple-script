# Error Handling

Error handling allows your program to deal with unexpected situations gracefully. Use `try`, `catch`, and `finally` blocks to handle errors.

## Try-Catch

```our_language
try {
    var result = riskyFunction();
} catch (error) {
    print("An error occurred: " + error.message);
}
```

## Finally

The finally block is executed regardless of whether an error occurred.

```our_language
try {
    var result = riskyFunction();
} catch (error) {
    print("An error occurred: " + error.message);
} finally {
    print("Cleanup code executed.");
}
```
