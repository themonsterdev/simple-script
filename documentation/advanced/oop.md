# Object-Oriented Programming

Object-oriented programming (OOP) is a programming paradigm based on the concept of objects. Our language supports OOP with classes and inheritance.

## Classes

A class is a blueprint for creating objects.

```our_language
class Person {
    constructor(name, age) {
        this.name = name;
        this.age = age;
    }

    greet() {
        print("Hello, my name is " + this.name);
    }
}

var alice = new Person("Alice", 30);
alice.greet(); // Outputs: Hello, my name is Alice
```

## Inheritance

Classes can inherit properties and methods from other classes.

```our_language
class Employee extends Person {
    constructor(name, age, jobTitle) {
        super(name, age);
        this.jobTitle = jobTitle;
    }

    work() {
        print(this.name + " is working as a " + this.jobTitle);
    }
}

var bob = new Employee("Bob", 25, "Developer");
bob.greet(); // Outputs: Hello, my name is Bob
bob.work();  // Outputs: Bob is working as a Developer
```
