#include <iostream>
#include <vector>
#include <deque>
using namespace std;


int main() {
    int t;  // Número de casos de prueba
    cin >> t;
    
    vector<vector<int>> results;  // Almacenar los resultados para cada caso de prueba
    
    // Leer todos los casos de prueba
    for (int test = 0; test < t; ++test) {
        int n;  // Longitud de la secuencia
        cin >> n;
        
        vector<int> b(n);
        for (int i = 0; i < n; ++i) {
            cin >> b[i];
        }
        
        deque<int> a;  // Para almacenar la secuencia restaurada
        bool insertLeft = true;  // Alternar entre insertar a la izquierda y derecha
        
        // Reconstruir la secuencia original 'a'
        for (int i = 0; i < n; ++i) {
            if (insertLeft) {
                a.push_front(b[i]);
            } else {
                a.push_back(b[i]);
            }
            insertLeft = !insertLeft;  // Alternar entre izquierda y derecha
        }
        
        // Guardar el resultado de esta secuencia
        vector<int> result(a.begin(), a.end());
        results.push_back(result);
    }
    
    // Imprimir todos los resultados al final
    for (const auto& result : results) {
        for (int num : result) {
            cout << num << " ";
        }
        cout << endl;
    }
    
    return 0;
}