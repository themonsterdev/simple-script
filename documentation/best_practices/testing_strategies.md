# Testing Strategies

Testing ensures your code works correctly. Here are some strategies for effective testing.

## Unit Testing

- Test individual units of code (functions, methods) in isolation.

Example:

```simple_script
function add(a, b) then
    return a + b
end

function testAdd() then
    assert(add(2, 3) == 5)
    assert(add(-1, 1) == 0)
end

testAdd()
```

## Integration Testing

Test how different units work together.

Example:

```simple_script
function multiply(a, b) then
    return a * b
end

function testMathOperations() then
    assert(add(multiply(2, 3), 4) == 10)
end

testMathOperations()
```
