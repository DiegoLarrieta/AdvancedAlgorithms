/*

Luis Diego Dominguez Larrieta
A01275640
Input 

2
3
72 17
44 23
31 24
1
26
6
64 26
85 22
52 4
99 18
39 13
54 9
4
23
20
20
26

Output

72
514

Complejidad 
O(C * P * N * W)
Donde C es el numero de casos , P es el numero de personas , N es el numero de objetos y W es el peso que cada persona puede cargar 
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int T;  // Número de casos de prueba
    cin >> T;

    vector<int> resultados; 

    while (T--) {
        int N;  // Número de objetos
        cin >> N;

        vector<pair<int, int>> items(N);  // Almacenamos los objetos como (precio, peso)
        for (int i = 0; i < N; ++i) {
            int P, W;
            cin >> P >> W;
            items[i] = {P, W};
        }

        int G;  // Número de personas en el grupo
        cin >> G;

        vector<int> maxWeight(G);  // Almacenamos el peso máximo que cada persona puede cargar
        for (int i = 0; i < G; ++i) {
            cin >> maxWeight[i];
        }

        int totalValue = 0;

        for (int i = 0; i < G; ++i) {
            int MW = maxWeight[i];  // Capacidad máxima de la mochila de la persona i
            vector<int> dp(MW + 1, 0);  // DP para mochila de capacidad MW

            // Algoritmo de la mochila 0/1
            for (int j = 0; j < N; ++j) {
                int price = items[j].first;
                int weight = items[j].second;

                // Recorremos de MW hacia atrás para evitar sobreescribir valores
                for (int w = MW; w >= weight; --w) {
                    dp[w] = max(dp[w], dp[w - weight] + price);
                }
            }

            // La persona i puede cargar un valor máximo dp[MW]
            totalValue += dp[MW];
        }

        // Imprimimos el valor total para este caso de prueba
        resultados.push_back(totalValue);
    }
     for (int resultado : resultados) {
        cout << resultado << endl;
    }
    return 0;
}
