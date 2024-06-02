# Testing Strategies

Testing ensures your code works correctly. Here are some strategies for effective testing.

## Unit Testing

- Test individual units of code (functions, methods) in isolation.

Example:

```our_language
function add(a, b) {
    return a + b;
}

function testAdd() {
    assert(add(2, 3) == 5);
    assert(add(-1, 1) == 0);
}

testAdd();
```

## Integration Testing

Test how different units work together.

Example:

```our_language
function multiply(a, b) {
    return a * b;
}

function testMathOperations() {
    assert(add(multiply(2, 3), 4) == 10);
}

testMathOperations();
```

## Mocking

Use mocking to test code that depends on external systems or resources.

Example:

```our_language
function fetchData(api) {
    return api.getData();
}

function testFetchData() {
    var mockApi = {
        getData: function() {
            return "mock data";
        }
    };
    assert(fetchData(mockApi) == "mock data");
}

testFetchData();
```
