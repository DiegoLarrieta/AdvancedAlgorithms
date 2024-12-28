#include <iostream>
#include <vector>

using namespace std;

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

const int INF = INT_MAX;

// Función para aplicar el algoritmo de Floyd-Warshall y encontrar la ruta con el mínimo máximo de intensidad sonora
void floydWarshall(int crossings, vector<vector<int>>& dist) {
    for (int k = 0; k < crossings; ++k) {
        for (int i = 0; i < crossings; ++i) {
            for (int j = 0; j < crossings; ++j) {
                // Verifica si existe un camino desde i a k y de k a j
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    // Actualiza la distancia con el mínimo máximo valor de intensidad sonora
                    dist[i][j] = min(dist[i][j], max(dist[i][k], dist[k][j]));
                }
            }
        }
    }
}

int main() {
    int cases;
    cin >> cases;
    for (int testCase = 1; testCase <= cases; ++testCase) {
        int C, S, Q;
        cin >> C >> S >> Q;

        // Inicializar la matriz de distancia con INF
        vector<vector<int>> dist(C, vector<int>(C, INF));

        // Establecer el valor 0 en la diagonal (distancia a sí mismo)
        for (int i = 0; i < C; ++i) {
            dist[i][i] = 0;
        }

        // Leer las calles y sus intensidades sonoras
        for (int i = 0; i < S; ++i) {
            int c1, c2, d;
            cin >> c1 >> c2 >> d;
            c1--; // Convertir a índice 0
            c2--; // Convertir a índice 0
            dist[c1][c2] = d;
            dist[c2][c1] = d;
        }

        // Aplicar el algoritmo de Floyd-Warshall
        floydWarshall(C, dist);

        // Mostrar los resultados para el caso actual
        cout << "Case " << testCase << ":\n";

        // Leer las consultas y mostrar los resultados
        for (int i = 0; i < Q; ++i) {
            int c1, c2;
            cin >> c1 >> c2;
            c1--; // Convertir a índice 0
            c2--; // Convertir a índice 0
            int result = dist[c1][c2];

            // Imprimir "no path" si no hay un camino entre los cruces
            if (result == INF) {
                cout << "no path\n";
            } else {
                cout << result << "\n";
            }
        }

        // Añadir una línea en blanco solo si no es el último caso
        if (testCase < cases) {
            cout << endl;
        }
    }

    return 0;
}

/*

Input

2
7 9 3
1 2 50
1 3 60
2 4 120
2 5 90
3 6 50
4 6 80
4 7 70
5 7 40
6 7 140
1 7
2 6
6 2
7 6 3
1 2 50
1 3 60
2 4 120
3 6 50
4 6 80
5 7 40
7 5
1 7
2 4

*/

/*
Output

Case 1:
no path
no path
Case 2:
1
1


*/