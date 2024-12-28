#include <iostream>

using namespace std;

void increment(int *value) { // Recibe un puntero a int
    (*value)++; // Desreferencia y modifica el valor
}

int main() {
    int number = 5;
    int *ptr = &number; // ptr apunta a la dirección de number

    cout << "Valor original: " << number << endl; // 5
    *ptr = 10; // Modifica number usando el puntero
    cout << "Valor después de cambiar *ptr: " << *ptr << endl; // 10

    increment(ptr); // Incrementa number usando el puntero
    cout << "Valor después de incrementar: " << number << endl; // 11

    // Muestra la dirección de memoria
    cout << "Dirección de number: " << ptr << endl;

    return 0;
}
