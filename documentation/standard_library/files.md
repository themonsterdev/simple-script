# File Handling

The standard library provides functions to handle file operations such as reading from and writing to files.

## Reading a File

```ts
var file = open("example.txt", "r")
var content = file.read()
print(content)
file.close()
```

## Writing to a File

```ts
var file = open("example.txt", "w")
file.write("This is a sample text.")
file.close()
```
