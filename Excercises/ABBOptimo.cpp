/*
4
20
40
10
30

Output
Nivel 0 : B
Nivel 1 : A D
Nivel 2 : C
Altura : 3
Promedio de Comparaciones : 1.70
*/

// Luis Diego Dominguez Larrieta A01275640
#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <climits>
#define INF INT_MAX

using namespace std;

// Función para calcular la raíz óptima y el costo mínimo del árbol binario de búsqueda óptimo
// Complejidad de O(N^3)
void optimalBST(const vector<int>& probabilities, vector<vector<int>>& root, vector<vector<double>>& cost, int n) {
    for (int i = 0; i < n; i++) {
        cost[i][i] = probabilities[i];
        root[i][i] = i;
    }
    
    for (int l = 2; l <= n; l++) { // l es la longitud de la cadena
        for (int i = 0; i <= n - l; i++) {
            int j = i + l - 1;
            cost[i][j] = INT_MAX;
            double sum = 0;
            for (int k = i; k <= j; k++) sum += probabilities[k];
            
            for (int k = i; k <= j; k++) {
                double c = (k > i ? cost[i][k - 1] : 0) + (k < j ? cost[k + 1][j] : 0) + sum;
                if (c < cost[i][j]) {
                    cost[i][j] = c;
                    root[i][j] = k;
                }
            }
        }
    }
}

// Función para clcular el nivel de cada nodo en el árbol óptimo
//Complejidad O(N)
void calculateLevels(const vector<vector<int>>& root, vector<string>& levels, int start, int end, int level, const vector<char>& nodes) {
    if (start > end) return;
    int r = root[start][end];
    if (level >= levels.size()) levels.resize(level + 1);
    levels[level] += nodes[r];
    levels[level] += ' ';
    
    calculateLevels(root, levels, start, r - 1, level + 1, nodes);
    calculateLevels(root, levels, r + 1, end, level + 1, nodes);
}

// Función para calcular el promedio de comparaciones
double calculateAverageComparisons(const vector<vector<double>>& cost, int n) {
    return cost[0][n - 1] / 100.0;
}

int main() {
    int n;
    cin >> n;
    
    vector<int> probabilities(n);
    vector<char> nodes(n);
    
    // Leer las probabilidades y Tambien asignar etiquetas a los nodos
    for (int i = 0; i < n; i++) {
        cin >> probabilities[i];
        nodes[i] = 'A' + i;
    }
    
    vector<vector<int>> root(n, vector<int>(n, 0));
    vector<vector<double>> cost(n, vector<double>(n, 0));
    
    // árbol óptimo
    optimalBST(probabilities, root, cost, n);
    
    // niveles del árbol
    vector<string> levels;
    calculateLevels(root, levels, 0, n - 1, 0, nodes);
    
    // nivel del árbol
    for (int i = 0; i < levels.size(); i++) {
        cout << "Nivel " << i << ": " << levels[i] << endl;
    }
    
    //  altura del árbol
    cout << "Altura: " << levels.size() << endl;
    

    double averageComparisons = calculateAverageComparisons(cost, n);
    cout << "Promedio de Comparaciones: " << fixed << setprecision(2) << averageComparisons << endl;
    
    return 0;
}
