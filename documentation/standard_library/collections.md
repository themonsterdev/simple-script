# Collections

Collections are data structures that hold multiple values. Our language provides several types of collections.

## Arrays

Arrays are ordered collections of items.

```our_language
var numbers = [1, 2, 3, 4, 5];
print(numbers[0]); // Outputs: 1
```

## Dictionaries

Dictionaries are collections of key-value pairs.

```our_language
var student = {
    "name": "Alice",
    "age": 21,
    "major": "Computer Science"
};

print(student["name"]); // Outputs: Alice
```

## Iterating Over Collections

```our_language
var fruits = ["apple", "banana", "cherry"];

for (var i = 0; i < fruits.length; i++) {
    print(fruits[i]);
}
```
