// Animal.h
// Archivo de cabecera que declara la clase Animal

#ifndef ANIMAL_H // Evita la inclusión múltiple
#define ANIMAL_H

#include <string>
using namespace std;

// Clase base Animal que representa un animal genérico
class Animal {
protected:
    string name;
    int age;

public:
    // Constructor parametrizado
    Animal(string name, int age);

    // Métodos para obtener información del animal
    string getName();
    int getAge();

    // Método virtual puro para emitir el sonido del animal
    virtual void makeSound() = 0; // Abstracción y Polimorfismo
};

#endif
