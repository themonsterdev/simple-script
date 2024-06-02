# Object-Oriented Programming

Object-oriented programming (OOP) is a programming paradigm based on the concept of objects. Our language supports OOP with classes and inheritance.

## Classes

A class is a blueprint for creating objects.

```simple_script
class Person {
    constructor(name, age) then
        this.name = name
        this.age = age
    end

    greet() then
        print("Hello, my name is " + this.name)
    end
end

var alice = new Person("Alice", 30)
alice.greet() // Outputs: Hello, my name is Alice
```

## Inheritance

Classes can inherit properties and methods from other classes.

```simple_script
class Employee extends Person {
    constructor(name, age, jobTitle) then
        super(name, age)
        this.jobTitle = jobTitle
    end

    work() then
        print(this.name + " is working as a " + this.jobTitle)
    end
end

var bob = new Employee("Bob", 25, "Developer")
bob.greet() // Outputs: Hello, my name is Bob
bob.work()  // Outputs: Bob is working as a Developer
```
