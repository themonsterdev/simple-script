# Switch Statements

Switch statements allow you to execute one block of code from multiple options based on the value of a variable.

## Syntax

```simple_script
var grade = 'B'

switch grade then
    case 'A' then
        print("Excellent")
    case 'B' then
        print("Good")
    case 'C' then
        print("Fair")
    default
        print("Poor")
end
```

## Example

```simple_script
var day = "Tuesday"

switch day then
    case "Monday" then
        print("Start of the week")
    case "Friday" then
        print("End of the work week")
    default
        print("Midweek days")
end
```
