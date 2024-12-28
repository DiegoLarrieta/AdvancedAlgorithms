/*
Luis Diego Dominguez Larrieta 
*/
// Complejidad: O(n*m)
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Función para encontrar la subcadena común más larga entre dos cadenas
int longestCommonSubstring(const string& s1, const string& s2) {
    int n = s1.length(), m = s2.length();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    int maxLength = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                maxLength = max(maxLength, dp[i][j]);
            }
        }
    }

    return maxLength;
}

int main() {
    int cases;
    cin >> cases;
    cin.ignore();  // Ignorar el salto de línea restante después de leer el número de casos

    vector<int> results;

    for (int i = 1; i <= cases; ++i) {
        string s1, s2;
        getline(cin, s1);  // Usar getline para leer la cadena completa incluyendo espacios
        getline(cin, s2);

        int result = longestCommonSubstring(s1, s2);
        results.push_back(result);  // Almacenar el resultado en un vector
    }

    // Ahora imprimir todos los resultados
    for (int i = 0; i < cases; ++i) {
        cout << "Case " << i + 1 << ": " << results[i] << endl;
    }

    return 0;
}
