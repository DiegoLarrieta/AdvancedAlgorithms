#include <iostream>
#include <vector>

using namespace std;

int main() {
    int numberCards;
    cin >> numberCards;  // Leer el número de cartas

    vector<int> values(numberCards);  // Crear un vector para almacenar los valores de las cartas
    for (int i = 0; i < numberCards; ++i) {
        cin >> values[i];  // Leer los valores de las cartas
    }

    int left = 0, right = numberCards - 1;  // Punteros a los extremos de las cartas
    int serejaPoints = 0, dimaPoints = 0;   // Puntos de Sereja y Dima

    bool serejaTurn = true;  // Sereja siempre comienza primero

    // Mientras queden cartas
    while (left <= right) {
        if (values[left] > values[right]) {
            // Si la carta de la izquierda es mayor
            if (serejaTurn) {
                serejaPoints += values[left];  // Sereja toma la carta
            } else {
                dimaPoints += values[left];    // Dima toma la carta
            }
            left++;  // Mover el puntero izquierdo
        } else {
            // Si la carta de la derecha es mayor o igual
            if (serejaTurn) {
                serejaPoints += values[right];  // Sereja toma la carta
            } else {
                dimaPoints += values[right];    // Dima toma la carta
            }
            right--;  // Mover el puntero derecho
        }
        serejaTurn = !serejaTurn;  // Cambiar el turno
    }

    // Imprimir los puntos finales de Sereja y Dima
    cout << serejaPoints << " " << dimaPoints << endl;

    return 0;
}
