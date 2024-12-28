#include <iostream>
#include <string>
#include <vector>
using namespace std;
/*
4
0111
5
10101
6
101010
7
1010110
1
1
2
10
2
11
10
1011011010
*/
int main() {
    int t; // Número de casos de prueba
    cin >> t;

    vector<int> results; // Almacenamos los resultados de todos los casos de prueba

    for (int i = 0; i < t; ++i) {
        int n;
        string s;
        cin >> n >> s;

        // Vamos a contar cuántas transiciones hay entre '0' y '1'
        int transitions = 0;
        
        for (int j = 1; j < n; ++j) {
            if (s[j] != s[j - 1]) {
                transitions++;
            }
        }

        // El tamaño más pequeño de la cadena inicial sería el número de transiciones + 1
        int min_initial_size = transitions + 1;

        // Guardamos el resultado en el vector, dividiendo entre 2 porque cada transicion representa dos movimientos
        results.push_back(min_initial_size / 2);
    }

    // Imprimimos todos los resultados una vez ingresados todos los inputs
    for (int result : results) {
        cout << result << endl;
    }

    return 0;
}

