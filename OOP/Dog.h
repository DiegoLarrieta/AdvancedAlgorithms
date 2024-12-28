// Dog.h
// Archivo de cabecera que declara la clase Dog

#ifndef DOG_H
#define DOG_H

#include "Animal.h"

// Clase Dog que hereda de Animal
class Dog : public Animal {
public:
    // Constructor que utiliza el constructor de Animal
    Dog(string name, int age);

    // Implementación del método makeSound específico para los perros
    void makeSound() override;
};

#endif
