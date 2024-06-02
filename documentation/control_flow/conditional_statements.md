# Conditional Statements

Conditional statements allow you to execute different blocks of code based on certain conditions. Our language supports `if`, `else if`, and `else` statements.

## If Statement

```our_language
var age = 18;

if (age >= 18) {
    print("You are an adult.");
}
```

## If-Else Statement

```our_language
var age = 16;

if (age >= 18) {
    print("You are an adult.");
} else {
    print("You are a minor.");
}
```

## Else-If Statement

```our_language
var score = 85;

if (score >= 90) {
    print("Grade: A");
} else if (score >= 80) {
    print("Grade: B");
} else if (score >= 70) {
    print("Grade: C");
} else {
    print("Grade: F");
}
```
