/*\
& REFERENCIA &
*/

#include <iostream>

using namespace std;

void increment(int &value) { // Pasar por referencia
    value++; // Modifica la variable original
}

void decrement(int &value){
  value --;
}

int main() {
    int number = 5;
    int &ref = number; // ref es una referencia a number o  como una copia 

    cout << "Valor original: " << number << endl; // 5
    ref = 10; // Modifica number a través de ref
    cout << "Valor después de cambiar ref: " << number << endl; // 10

    increment(number); // Incrementa number por referencia
    cout << "Valor después de incrementar: " << number << endl; // 11

    return 0;
}
