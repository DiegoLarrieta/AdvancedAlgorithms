#include <iostream>
#include <queue>
#include <vector>
using namespace std;
/*
Luis Diego Dominguez Larrieta 
A01275640

Complejidad canFormDesiredOrder -> Exponencial
Complejidad trains -> Exponencial
Complejidad Main -> O(C*N) C = Numero de casos y N numero total de elementos en cada caso
*/

bool canFormDesiredOrder(queue<int>& train1, queue<int>& train2, const vector<int>& desired, int index) {
    // Caso base: Si hemos procesado toda la secuencia deseada, hemos tenido éxito
    if (index == desired.size()) {
        return true;
    }

    // Verifica si el siguiente vagón en la secuencia deseada puede ser tomado de train1
    if (!train1.empty() && train1.front() == desired[index]) {
        train1.pop();  // Tomar el vagón de train1
        if (canFormDesiredOrder(train1, train2, desired, index + 1)) {
            return true;  // Éxito al tomar del train1
        }
        train1.push(desired[index]);  // Deshace la acción si no fue exitosa
    }

    // Verifica si el siguiente vagón en la secuencia deseada puede ser tomado de train2
    if (!train2.empty() && train2.front() == desired[index]) {
        train2.pop();  // Tomar el vagón de train2
        if (canFormDesiredOrder(train1, train2, desired, index + 1)) {
            return true;  // Éxito al tomar del train2
        }
        train2.push(desired[index]);  // Deshace la acción si no fue exitosa
    }

    // Si ninguna de las opciones funciona, no es posible formar el orden deseado
    return false;
}

string trains(queue<int> train1, queue<int> train2, const vector<int>& desired) {
    if (canFormDesiredOrder(train1, train2, desired, 0)) {
        return "possible";
    } else {
        return "not possible";
    }
}

int main() {
    vector<pair<pair<queue<int>, queue<int>>, vector<int>>> cases;  // Vector que almacenar los casos de prueba
    int N1, N2;

    while (true) {
        cin >> N1 >> N2;
        if (N1 == 0 && N2 == 0) {
            break;  // Salir si se encuentra el caso "0 0"
        }

        queue<int> train1, train2;
        vector<int> desired;

        // Lee los vagones del primer tren
        for (int i = 0; i < N1; ++i) {
            int item;
            cin >> item;
            train1.push(item);
        }

        // Lee los vagones del segundo tren
        for (int i = 0; i < N2; ++i) {
            int item;
            cin >> item;
            train2.push(item);
        }

        // Lee la secuencia deseada
        for (int i = 0; i < N1 + N2; ++i) {
            int item;
            cin >> item;
            desired.push_back(item);
        }

        // Almacena el caso en el vector
        cases.push_back({{train1, train2}, desired});
    }

    // Procesa todos los casos y mostrar los resultados
    for (const auto& caseData : cases) {
        // Copiar colas para no modificar las originales
        queue<int> train1Copy = caseData.first.first;
        queue<int> train2Copy = caseData.first.second;
        const vector<int>& desired = caseData.second;

        // Muestra el resultado del caso actual
        cout << trains(train1Copy, train2Copy, desired) << endl;
    }

    return 0;
}
