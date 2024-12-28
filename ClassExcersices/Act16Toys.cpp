/*
Sample Input 

5 6 0 10 60 0
3 1
4 3
6 8
10 10
15 30
1 5
2 1
2 8
5 5
40 10
7 9
4 10 0 10 100 0
20 20
40 40
60 60
80 80
5 10
15 10
25 10
35 10
45 10
55 10
65 10
75 10
85 10
95 10
0


Sample Output 
0: 2
1: 1
2: 1
3: 1
4: 0
5: 1
0: 2
1: 2
2: 2
3: 2
4: 2

*/

//Luis Diego Dominguez Larrieta A01275640

#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

// Funcin para determinar en qué particiOn cae un juguete
//Complejidad O(N)
int findPartition(const vector<int>& partitions, int x) {
    if (x < partitions[0]) {
        return 0; // Juguete cae en el primer contenedor
    }
    for (int i = 1; i < partitions.size(); i++) {
        if (x < partitions[i]) {
            return i; // Juguete cae en la particion correspondiente
        }
    }
    return partitions.size(); // Juguete cae en el ultimo contenedor
}

int main() {
    string line;
    vector<string> results; // Almacena los resultados para cada caso de prueba

    while (true) {
        // Leer la primera linea de un caso de prueba
        getline(cin, line);
        stringstream ss(line);
        int n, m, x1, y1, x2, y2;
        ss >> n >> m >> x1 >> y1 >> x2 >> y2;

        if (n == 0) break; // Terminamos cuando n es 0

        // Lee las particiones O(N)
        vector<int> partitions(n);
        for (int i = 0; i < n; i++) {
            getline(cin, line);
            stringstream partStream(line);
            int u, l;
            partStream >> u >> l;
            partitions[i] = u;
        }

        // Lee las posiciones de los juguetes
        vector<int> toyCounts(n + 1, 0); // n+1 contenedores (0 a n)
        for (int i = 0; i < m; i++) {
            getline(cin, line);
            stringstream toyStream(line);
            int x, y;
            toyStream >> x >> y;
            int bin = findPartition(partitions, x); // Determinar la partición cae el juguete
            toyCounts[bin]++;
        }

        // Formatear el resultado para este caso de prueba
        stringstream result;
        for (int i = 0; i <= n; i++) {
            result << i << ": " << toyCounts[i] << endl;
        }
        results.push_back(result.str()); // Guardamos el resultado
    }

    // Imprimir todos los resultados juntos
    for (size_t i = 0; i < results.size(); i++) {
        cout << results[i];
        if (i < results.size() - 1) {

        }
    }

    return 0;
}
