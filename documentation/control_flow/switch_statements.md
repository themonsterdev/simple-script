# Switch Statements

Switch statements allow you to execute one block of code from multiple options based on the value of a variable.

## Syntax

```ts
var grade = 'B'

switch grade
    case 'A':
        print("Excellent")
    case 'B':
        print("Good")
    case 'C':
        print("Fair")
    default:
        print("Poor")
end
```

## Example

```ts
var day = "Tuesday"

switch day
    case "Monday"
        print("Start of the week")
    case "Friday":
        print("End of the work week")
    default:
        print("Midweek days")
end
```
