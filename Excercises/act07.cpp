/*
Luis Diego Dominguez Larrieta
*/
// Complejidad: O(n*m)

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int longestCommonSubsequence(const string& s1, const string& s2) {
    int n = s1.size(), m = s2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    // Llenar la matriz dp
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;  // Si los caracteres coinciden
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[n][m];  
}

int main() {
    int cases;
    cin >> cases;

    vector<int> results;  // Vector para almacenar los resultados de cada caso

    for (int i = 1; i <= cases; i++) {
        string s1, s2;
        cin >> s1 >> s2;
        int result = longestCommonSubsequence(s1, s2);
        results.push_back(result);  // Guardar el resultado
    }

    // Ahora imprimimos todos los resultados al final
    for (int i = 0; i < cases; i++) {
        cout << "Case " << i + 1 << ": " << results[i] << endl;
    }

    return 0;
}
