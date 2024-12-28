// main.cpp
#include <iostream>
#include "Dog.h" // Incluye las declaraciones de Dog
#include "Cat.h" // Incluye las declaraciones de Cat

using namespace std;

// Implementación del constructor de Animal
Animal::Animal(string name, int age) {
    this->name = name;
    this->age = age;
}

// Implementación de los métodos getName y getAge de Animal
string Animal::getName() {
    return name;
}

int Animal::getAge() {
    return age;
}

// Implementación del constructor de Dog
Dog::Dog(string name, int age) : Animal(name, age) {}

// Implementación del método makeSound para Dog
void Dog::makeSound() {
    cout << name << " says: Woof! Woof!" << endl;
}

// Implementación del constructor de Cat
Cat::Cat(string name, int age) : Animal(name, age) {}

// Implementación del método makeSound para Cat
void Cat::makeSound() {
    cout << name << " says: Meow! Meow!" << endl;
}

int main() {
    // Crear objetos de Dog y Cat
    Dog dog("Buddy", 3);
    Cat cat("Whiskers", 2);

    // Mostrar información y sonidos de los animales
    cout << dog.getName() << " is " << dog.getAge() << " years old." << endl;
    dog.makeSound(); // Salida: Buddy says: Woof! Woof!

    cout << cat.getName() << " is " << cat.getAge() << " years old." << endl;
    cat.makeSound(); // Salida: Whiskers says: Meow! Meow!

    // Demostración de polimorfismo
    Animal* animalPtr;

    animalPtr = &dog;
    animalPtr->makeSound(); // Polimorfismo: Woof! Woof!

    animalPtr = &cat;
    animalPtr->makeSound(); // Polimorfismo: Meow! Meow!

    return 0;
}
