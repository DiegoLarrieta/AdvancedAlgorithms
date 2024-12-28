#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; // Número de casos de prueba
    cin >> t;

    vector<pair<int, vector<int>>> test_cases(t);

    // Leer todos los datos de entrada
    for (int i = 0; i < t; ++i) {
        int n; // Longitud del array
        cin >> n;
        vector<int> a(n);

        for (int j = 0; j < n; ++j) {
            cin >> a[j];
        }

        test_cases[i] = make_pair(n, a);
    }

    vector<string> results; // Vector para almacenar los resultados

    // Procesar cada caso de prueba
    for (const auto& test_case : test_cases) {
        int n = test_case.first;
        vector<int> a = test_case.second;
        
        vector<int> odds, evens;

        // Separar pares e impares
        for (int x : a) {
            if (x % 2 == 0) {
                evens.push_back(x);
            } else {
                odds.push_back(x);
            }
        }

        // Ordenar los pares y los impares
        sort(evens.begin(), evens.end());
        sort(odds.begin(), odds.end());

        // Reconstruir el array
        vector<int> sorted_a = a;
        int even_index = 0, odd_index = 0;

        for (int i = 0; i < n; ++i) {
            if (a[i] % 2 == 0) {
                sorted_a[i] = evens[even_index++];
            } else {
                sorted_a[i] = odds[odd_index++];
            }
        }

        // Verificar si el array resultante está ordenado
        bool can_sort = is_sorted(sorted_a.begin(), sorted_a.end());

        if (can_sort) {
            results.push_back("YES");
        } else {
            results.push_back("NO");
        }
    }

    // Imprimir todos los resultados
    for (const auto& result : results) {
        cout << result << endl;
    }

    return 0;
}