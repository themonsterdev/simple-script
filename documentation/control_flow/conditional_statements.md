# Conditional Statements

Conditional statements allow you to execute different blocks of code based on certain conditions. Simple Script supports `if`, `else if`, and `else` statements.

## If Statement

```simple_script
var age = 18

if age >= 18 then
    print("You are an adult.")
end
```

## If-Else Statement

```simple_script
var age = 16

if age >= 18 then
    print("You are an adult.")
else
    print("You are a minor.")
end
```

## Else-If Statement

```simple_script
var score = 85

if score >= 90 then
    print("Grade: A")
else if score >= 80 then
    print("Grade: B")
else if score >= 70 then
    print("Grade: C")
else
    print("Grade: F")
end
```
