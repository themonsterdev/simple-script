# Examples

This section provides practical examples of code snippets that demonstrate the usage of various grammatical constructs in the Simple Script language.

## Example 1: Variable Declaration and Assignment

```simple_script
var age = 25
var name = "John"
print(`Name: ${name}, Age: ${age}`)
```

## Example 2: Function Definition and Invocation

```simple_script
function add(a, b) then
    return a + b
end

var result = add(5, 3)
print(`Sum: ${result}`)
```

## Example 3: Loop and Conditional Statements

```simple_script
var i = 0
while i < 5 then
    if i % 2 == 0 then
        print(`${i} is even`)
    else
        print(`${i} is odd`)
    end
    i++
end
```
