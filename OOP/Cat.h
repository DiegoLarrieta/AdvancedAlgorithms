// Cat.h
// Archivo de cabecera que declara la clase Cat

#ifndef CAT_H
#define CAT_H

#include "Animal.h"

// Clase Cat que hereda de Animal
class Cat : public Animal {
public:
    // Constructor que utiliza el constructor de Animal
    Cat(string name, int age);

    // Implementación del método makeSound específico para los gatos
    void makeSound() override;
};

#endif
