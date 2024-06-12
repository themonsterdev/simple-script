# Error Handling

Error handling allows your program to deal with unexpected situations gracefully. Use `try`, `catch`, and `finally` blocks to handle errors.

## Try-Catch

```ts
try
    var result = riskyFunction()
catch error
    print(`An error occurred: ${error.message}`)
end
```

## Finally

The finally block is executed regardless of whether an error occurred.

```ts
try
    var result = riskyFunction()
catch error
    print(`An error occurred: ${error.message}`)
finally
    print("Cleanup code executed.")
end
```
